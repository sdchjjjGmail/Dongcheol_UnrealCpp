// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ActionCharacter.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Player/ResourceComponent.h"
#include "Player/StatusComponent.h"
#include "Player/WeaponManagerComponent.h"
#include "Weapon/WeaponActor.h"
#include "Weapon/ConsumableWeapon.h"
#include "Weapon/ReinforcedWeaponActor.h"
#include "Weapon/UsedWeapon.h"
#include "Interface/Pickupable.h"
#include "Item/PickupActor.h"

// Sets default values
AActionCharacter::AActionCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 350.0f;
	SpringArm->SocketOffset = FVector(0, 0, 250);
	SpringArm->bUsePawnControlRotation = true;	// 스프링암의 회전을 컨트롤러에 맞춤

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(SpringArm);
	PlayerCamera->SetRelativeRotation(FRotator(-20.0f, 0.0f, 0.0f));

	DropLocation = CreateDefaultSubobject<USceneComponent>(TEXT("DropLocation"));
	DropLocation->SetupAttachment(RootComponent);
	DropLocation->SetRelativeLocation(FVector(80.0f, 30.0f, 0.0f));

	Resource = CreateDefaultSubobject<UResourceComponent>(TEXT("PlayerResource"));
	Status = CreateDefaultSubobject<UStatusComponent>(TEXT("PlayerStatus"));
	WeaponManager = CreateDefaultSubobject<UWeaponManagerComponent>(TEXT("WeaponManager"));

	bUseControllerRotationYaw = false;	// 컨트롤러의 Yaw 회전 사용 안함
	GetCharacterMovement()->bOrientRotationToMovement = true;	// 이동 방향으로 캐릭터 회전
	GetCharacterMovement()->RotationRate = FRotator(0, 360, 0);
}

// Called when the game starts or when spawned
void AActionCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (GetMesh())
	{
		AnimInstance = GetMesh()->GetAnimInstance();	// ABP 객체 가져오기
	}
	if (Resource)
	{
		if (Status)
		{
			Resource->SetMaxHealth((Status->GetAgility() + Status->GetVitalilty()) * 10);
			Resource->SetMaxStamina(Status->GetVitalilty() * 10);
		}
		Resource->OnStaminaEmpty.AddDynamic(this, &AActionCharacter::SetWalkMode);
	}

	if (GetMesh())
	{
		AnimInstance = GetMesh()->GetAnimInstance();
	}

	// 게임 진행 중에 자주 변경되는 값은 시작 시점에서 리셋을 해주는 것이 좋다.
	bIsSprint = false;
	OnActorBeginOverlap.AddDynamic(this, &AActionCharacter::OnCharacterOverlap);
}

// Called every frame
void AActionCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SpendRunStamina(DeltaTime);
}

// Called to bind functionality to input
void AActionCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* enhanced = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (enhanced)	// 입력 컴포넌트가 향상된 입력 컴포넌트일 때
	{
		enhanced->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AActionCharacter::OnMoveInput);
		enhanced->BindActionValueLambda(IA_Sprint, ETriggerEvent::Started, 
			[this](const FInputActionValue& _) {
				SetSprintMode();
			});
		enhanced->BindActionValueLambda(IA_Sprint, ETriggerEvent::Completed,
			[this](const FInputActionValue& _) {
				SetWalkMode();
			});
		enhanced->BindAction(IA_Roll, ETriggerEvent::Triggered, this, &AActionCharacter::OnRollInput);
		enhanced->BindAction(IA_Attack, ETriggerEvent::Triggered, this, &AActionCharacter::OnAttackInput);
	}
}

void AActionCharacter::AddItem_Implementation(EItemCode Code, int32 Count)
{
	//const UEnum* EnumPtr = StaticEnum<EItemCode>();
	//UE_LOG(LogTemp, Log, TEXT("아이템 추가 : %s"),
	//	*EnumPtr->GetDisplayNameTextByValue(static_cast<int8>(Code)).ToString());
	EquipWeapon(Code);
	CurrentWeapon->OnWeaponPickedup(Count);
}

void AActionCharacter::SetCollisionOn()
{
	UE_LOG(LogTemp, Log, TEXT("set Hit On"));
	//OnWeaponCollisionOn.Broadcast();
	
	if (CurrentWeapon.IsValid())
	{
		CurrentWeapon->AttackEnable();
	}
}

void AActionCharacter::SetCollisionOff()
{
	UE_LOG(LogTemp, Log, TEXT("set Hit Off"));
	//OnWeaponCollisionOff.Broadcast();

	if (CurrentWeapon.IsValid())
	{
		CurrentWeapon->AttackDisable();
	}
}

void AActionCharacter::TestDropUsedWeapon()
{
	DropWeapon(CurrentWeapon->GetWeaponID());
}

void AActionCharacter::TestDropCurrentWeapon()
{
	DropCurrentWeapon(CurrentWeapon->GetWeaponID());
}

void AActionCharacter::EquipWeapon(EItemCode WeaponCode)
{
	if (CurrentWeapon.IsValid())
	{
		if (CurrentWeapon->GetWeaponID() != EItemCode::BasicWeapon 
			&& WeaponCode != CurrentWeapon->GetWeaponID()
			&& CurrentWeapon->CanAttack())
		{
			DropCurrentWeapon(CurrentWeapon->GetWeaponID());
		}

		// 장비하고 있던 무기 해제
		CurrentWeapon->WeaponActivate(false);
	}
	// WeaponCode에 해당하는 무기 장비
	CurrentWeapon = WeaponManager->GetEquippedWeapon(WeaponCode);
	CurrentWeapon->WeaponActivate(true);
}

void AActionCharacter::DropWeapon(EItemCode WeaponCode)
{
	UE_LOG(LogTemp, Log, TEXT("다쓴 무기 버림"));
	if (TSubclassOf<AUsedWeapon> usedClass = WeaponManager->GetUsedWeaponClass(WeaponCode))
	{
		GetWorld()->SpawnActor<AActor>(
			usedClass,
			DropLocation->GetComponentLocation(),
			GetActorRotation());
	}
}

void AActionCharacter::OnMoveInput(const FInputActionValue& InValue)
{
	FVector2D inputDirection = InValue.Get<FVector2D>();
	//UE_LOG(LogTemp, Log, TEXT("Dir : (%.1f, %.1f)"), inputDirection.X, inputDirection.Y);
	//UE_LOG(LogTemp, Log, TEXT("Dir : (%s)"), *inputDirection.ToString());
	FVector moveDirection(inputDirection.Y, inputDirection.X, 0.0f);

	FQuat controlYawRotation = FQuat(FRotator(0, GetControlRotation().Yaw, 0));	// 컨트롤러의 Yaw회전을 따로 뽑아와서
	moveDirection = controlYawRotation.RotateVector(moveDirection);	// 이동 방향에 적용
	
	AddMovementInput(moveDirection);
}

void AActionCharacter::OnRollInput(const FInputActionValue& InValue)
{
	if (AnimInstance.IsValid())
	{
		if (!AnimInstance->IsAnyMontagePlaying() 
			&& Resource->HasEnoughStamina(RollStaminaCost))	// 몽타주 재생중이 아니고 충분한 스태미너가 있을 때만 작동
		{
			//if (!GetLastMovementInputVector().IsNearlyZero())	// 입력을 하는 중에만 즉시 회전
			//{
			//	SetActorRotation(GetLastMovementInputVector().Rotation());	// 마지막 입력 방향으로 즉시 회전 시키기
			//}
			Resource->AddStamina(-RollStaminaCost);	// 스태미너 감소
			PlayAnimMontage(RollMontage);
		}
	}
}

void AActionCharacter::OnAttackInput(const FInputActionValue& InValue)
{
	// 애님 인스턴스가 있고, 스태미너 충분하고, 현재 무기가 공격을 할 수 있어야 한다.
	if (AnimInstance.IsValid() && Resource->HasEnoughStamina(AttackStaminaCost)
		&& (CurrentWeapon.IsValid() && CurrentWeapon->CanAttack()))
	{
		if (!AnimInstance->IsAnyMontagePlaying())
		{
			PlayAnimMontage(AttackMontage); // 몽타주 재생

			FOnMontageEnded onMontageEnded;
			onMontageEnded.BindUObject(this, &AActionCharacter::OnAttackMontageEnded);
			AnimInstance->Montage_SetEndDelegate(onMontageEnded); // 몽타주가 끝났을 때 델리게이트 발송(플레이 이후에 등록해야 함)

			Resource->AddStamina(-AttackStaminaCost);	// 스태미너 감소
			if (CurrentWeapon.IsValid())
			{
				CurrentWeapon->OnAttack(); // 무기 공격 시 처리(횟수 차감)
			}
		}
		else if (AnimInstance->GetCurrentActiveMontage() == AttackMontage)
		{
			SectionJumpForComboPractice(); // 콤보 공격 시도
		}
	}
}

void AActionCharacter::SetSprintMode()
{
	//UE_LOG(LogTemp, Warning, TEXT("달리기 모드"));
	if (Resource->GetCurrentStamina() > 1.0f)
	{
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
		bIsSprint = true;
	}
}

void AActionCharacter::SetWalkMode()
{
	//UE_LOG(LogTemp, Warning, TEXT("걷기 모드"));
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	bIsSprint = false;
}

void AActionCharacter::OnCharacterOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	UE_LOG(LogTemp, Log, TEXT("Character Overlapped with : %s"), *OtherActor->GetName());

	// Cast를 이용한 인터페이스 사용
	//IPickupable* test = Cast<IPickupable>(OtherActor);
	//if (test)
	//{
	//	IPickupable::Execute_OnPickup(OtherActor); // 만약에 블루프린트 구현이 있을 경우, 블루프린트의 구현이 실행된다.
	//	// test->OnPickup_Implementation(); // 블루프린트 구현을 무시	
	//}

	// Implements를 이용한 인터페이스 사용
	if (OtherActor->Implements<UPickupable>()) // OtherActor가 IPickupable 인터페이스를 구현했는지 확인
	{
		IPickupable::Execute_OnPickup(OtherActor, this); // 구현이 되어 있으면 실행
	}
}

void AActionCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	UE_LOG(LogTemp, Log, TEXT("공격 몽타주가 끝남"));
	if (CurrentWeapon.IsValid() && !CurrentWeapon->CanAttack()) // CurrentWeapon이 공격할수 없으면(=사용 횟수가 안남았다)
	{
		DropWeapon(CurrentWeapon->GetWeaponID());
		EquipWeapon(EItemCode::BasicWeapon);
	}
}

void AActionCharacter::SectionJumpForCombo()
{
	if (SectionJumpNotify.IsValid() && bComboReady)
	{
		UAnimMontage* current = AnimInstance->GetCurrentActiveMontage();
		AnimInstance->Montage_SetNextSection( // 다음 섹션으로 점프하기
			AnimInstance->Montage_GetCurrentSection(current), // 현재 섹션
			SectionJumpNotify->GetNextSectionName(), // 다음 섹션의 이름
			current // 실행될 몽타주
		);
		bComboReady = false;
		Resource->AddStamina(-AttackStaminaCost);	// 스태미너 감소
	}
}

void AActionCharacter::SectionJumpForComboPractice()
{
	if (ComnoSectionJumpNotify.IsValid() && bComboReady)
	{
		AnimInstance->Montage_JumpToSection(ComnoSectionJumpNotify->GetNextSectionName());
		bComboReady = false;
		Resource->AddStamina(-AttackStaminaCost);	// 스태미너 감소
		if (CurrentWeapon.IsValid())
		{
			CurrentWeapon->OnAttack();
		}
	}
}

void AActionCharacter::SpendRunStamina(float InDeltaTime)
{
	if (bIsSprint && !GetVelocity().IsNearlyZero() 
		&& AnimInstance.IsValid() && !AnimInstance->IsAnyMontagePlaying())	// 달리기 모드인 상태에서 움직이면 스태미너를 소비한다.
	{
		Resource->AddStamina(-SprintStaminaCost * InDeltaTime);	// 스태미너 감소
	}
}

void AActionCharacter::SetTrailState(bool TrailOn)
{
	if (CurrentWeapon.IsValid())
	{
		if (TrailOn)
		{
			CurrentWeapon->TrailEnable();
		}
		else
		{
			CurrentWeapon->TrailDisable();
		}
	}
}

void AActionCharacter::DropCurrentWeapon(EItemCode WeaponCode)
{
	if (CurrentWeapon.IsValid() && CurrentWeapon->GetWeaponID() != EItemCode::BasicWeapon)
	{
		if (TSubclassOf<APickupActor> pickupClass = WeaponManager->GetPickupWeaponClass(WeaponCode))
		{
			APickupActor* pickup = GetWorld()->SpawnActor<APickupActor>(
				*pickupClass,
				DropLocation->GetComponentLocation(),
				GetActorRotation());
			
			// 새로 생긴 픽업에 남은 횟수 넣기
			AConsumableWeapon* conWeapon = Cast<AConsumableWeapon>(CurrentWeapon);
			pickup->SetPickupCount(conWeapon->GetRemainingUseCount());

			FVector velocity = (GetActorForwardVector() + GetActorUpVector()) * 300.0f;
			pickup->AddImpulse(velocity);
		}
	}
}
