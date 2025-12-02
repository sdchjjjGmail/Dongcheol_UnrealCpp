// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/InventoryComponent.h"
#include "Interface/UsableItem.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	Slots.SetNum(InventorySize);
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInventoryComponent::AddGold(int32 Income)
{
	UE_LOG(LogTemp, Log, TEXT("AddGold : %d"), Income);
	Gold += Income;
	OnInventoryGoldChanged.ExecuteIfBound(Gold);
}

int32 UInventoryComponent::AddItem(UItemDataAsset* InItemData, int32 InQuantity)
{
	// 1. 같은 종류의 아이템이 들어있는 슬롯이 있는지 찾기
	//	1-1. 같은 종류의 아이템이 있으면 InQuantity 만큼 추가를 시도
	//	1-2. 추가하고 남은 아이템이 있으면 다음 1번 반복
	//	1-3. 추가하고 남은 아이템이 없으면 return 0; 하고 종료
	// 2. 같은 종류의 아이템이 없다면
	//	2-1 빈칸이 있는지 찾기
	//	2-2 빈칸이 있으면 빈칸에 아이템 추가 시도
	//	2-3 추가하고 남은 아이템이 있으면 2번 반복
	//	2-4 추가하고 남은 아이템이 없으면 return 0; 하고 종료
	// 3. 남아있는 InQuantity를 리턴하고 종료.

	int32 remainingCount = InQuantity;
	if (InItemData && InQuantity > 0)
	{
		// 같은 종류의 아이템이 들어있는 슬롯을 찾아 추가하기
		int32 startIndex = 0;
		while (remainingCount > 0) // remainingCount가 남아있는 한 반복
		{
			int32 foundIndex = FindSlotWithItem(InItemData, startIndex); // 같은 종류의 아이템이 들어있고, 공간에 여유가 있는 슬롯 찾기 시도
			if (foundIndex == UInventoryComponent::InventoryFail)
			{
				break;
			}

			// 같은 종류의 아이템이 들어있는 슬롯을 찾았다
			FInvenSlot& slot = Slots[foundIndex];
			int32 availableCount = slot.ItemData->ItemMaxStackCount - slot.GetCount(); // 추가 가능한 개수가 몇개인지 확인
			if (availableCount > 0) // 추가가 가능하면
			{
				int32 amountToAdd = FMath::Min(availableCount, remainingCount); // 추가량 결정
				SetItemAtIndex(foundIndex, InItemData, slot.GetCount() + amountToAdd); // 추가량만큼 추가
				remainingCount -= amountToAdd; // remainingCount을 슬롯에 추가한 만큼 감소
			}

			startIndex = foundIndex + 1; // FindSlotWithItem에서 현재 슬롯 다음부터 찾게 하기
		}

		// 같은 종류의 아이템이 들어있는 슬롯이 없으니 빈칸에 추가하기
		while (remainingCount > 0) // remainingCount가 남아있는 한 반복(빈슬롯이 없으면 break;)
		{
			int32 emptyIndex = FindEmptySlot();
			if (emptyIndex == UInventoryComponent::InventoryFail)
			{
				break; // 빈 슬롯이 없다.
			}
			UE_LOG(LogTemp, Log, TEXT("emptyIndex : %d"), emptyIndex);
			int32 amountToAdd = FMath::Min(InItemData->ItemMaxStackCount, remainingCount); // 추가량 결정
			SetItemAtIndex(emptyIndex, InItemData, amountToAdd); // 추가량만큼 추가
			remainingCount -= amountToAdd; // remainingCount을 슬롯에 추가한 만큼 감소
		}
		// 같은 종류의 아이템이 들어있는 슬롯과 빈슬롯을 모두 채우고도 아이템의 수가 남아있다.
	}
	return remainingCount;
}

void UInventoryComponent::UseItem(int32 InUseIndex)
{
	FInvenSlot* slot = GetSlotData(InUseIndex);
	if (slot->ItemData && slot->ItemData->Implements<UUsableItem>())
	{
		UE_LOG(LogTemp, Log, TEXT("InUseIndex : %d used"), InUseIndex);
		IUsableItem::Execute_UseItem(slot->ItemData, GetOwner());

		UpdateSlotCount(InUseIndex, -1);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("InUseIndex : %d 슬롯은 비어있거나 사용할 수 없는 아이템"), InUseIndex);
	}
}

void UInventoryComponent::SetItemAtIndex(int32 InSlotIndex, UItemDataAsset* InItemData, int32 InQuantity)
{
	if (IsValidIndex(InSlotIndex))
	{
		FInvenSlot& TargetSlot = Slots[InSlotIndex];

		TargetSlot.ItemData = InItemData;
		TargetSlot.SetCount(InQuantity); // InCount가 0이면 자동 Clear
		//UE_LOG(LogTemp, Log, TEXT("SetItemAtIndex %d, %s, %d개"), InSlotIndex, *InItemData->GetName(), InQuantity);
		OnInventorySlotChanged.ExecuteIfBound(InSlotIndex);
	}
}

void UInventoryComponent::UpdateSlotCount(int32 InSlotIndex, int32 InDeltaCount)
{
	UE_LOG(LogTemp, Log, TEXT("UpdateSlotCount : %d, %d"), InSlotIndex, InDeltaCount);
	if (IsValidIndex(InSlotIndex))
	{
		FInvenSlot& TargetSlot = Slots[InSlotIndex];
		if (TargetSlot.IsEmpty())
		{
			return; // 슬롯이 비어있으면 변화할 수 없음
		}
		
		int32 NewCount = TargetSlot.GetCount() + InDeltaCount;
		SetItemAtIndex(InSlotIndex, TargetSlot.ItemData, NewCount);
	}
}

void UInventoryComponent::ClearSlotAtIndex(int32 InSlotIndex)
{
	//if (IsValidIndex(InSlotIndex))
	//{
		//FInvenSlot& TargetSlot = Slots[InSlotIndex];
		//TargetSlot.Clear();
		//OnInventorySlotChanged.ExecuteIfBound(InSlotIndex);
	//}
		SetItemAtIndex(InSlotIndex, nullptr, 0);
}

FInvenSlot* UInventoryComponent::GetSlotData(int32 InSlotIndex)
{
	check(IsValidIndex(InSlotIndex));
	/*
		check : 거짓이면 프로그램 종료. shipping 빌드에 포함 안됨.
		verify : 거짓이면 프로그램 종료. shipping 빌드에 포함(검사는 안함).
		ensure : 거짓이면 로그 출력하고 계속. shipping 빌드에 포함
	*/
	
	return !Slots.IsEmpty() ? &Slots[InSlotIndex] : nullptr;
}

void UInventoryComponent::EditIventorySlot(int32 PrevIndex, int32 InSlotIndex, UItemDataAsset* InItemData, int32 InQuantity)
{
	if (Slots[InSlotIndex].IsEmpty())
	{
		SetItemAtIndex(InSlotIndex, InItemData, InQuantity);
		ClearSlotAtIndex(PrevIndex);
	}
	else
	{
		UItemDataAsset* tempData = Slots[InSlotIndex].ItemData;
		int32 tempQuan = Slots[InSlotIndex].GetCount();
		SetItemAtIndex(InSlotIndex, InItemData, InQuantity);
		SetItemAtIndex(PrevIndex, tempData, tempQuan);
	}
}

int32 UInventoryComponent::FindSlotWithItem(UItemDataAsset* InItemData, int32 InStartIndex)
{
	int32 result = UInventoryComponent::InventoryFail;
	int32 size = Slots.Num();
	for (int32 i = InStartIndex; i < size; i++)
	{
		if (Slots[i].ItemData == InItemData && !Slots[i].IsStackFull())
		{
			result = i;
			break;
		}
	}
	return result;
}

int32 UInventoryComponent::FindEmptySlot()
{
	int32 result = UInventoryComponent::InventoryFail;
	int32 size = Slots.Num();
	for (int32 i = 0; i < size; i++)
	{
		if (Slots[i].IsEmpty())
		{
			result = i;
			break;
		}
	}
	return result;
}
