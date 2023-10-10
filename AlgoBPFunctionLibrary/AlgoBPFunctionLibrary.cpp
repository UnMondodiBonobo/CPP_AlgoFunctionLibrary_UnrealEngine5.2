// Free to use WIP AlgoBPFunctionLibrary, October 8 2023, Alessandro Profera

#include "AlgoBPFunctionLibrary.h"
#include <InstancedStruct.h>

const UObject* UAlgoBPFunctionLibrary::BP_FindByPredicate_ConstObject(UObject* InOuter,
	const TArray<UObject*>& InElementsToCheck,
	FName InPredicateName)
{
	UFunction* FoundFunction = Internal_FindPredicate(InOuter, InPredicateName);
	if (!FoundFunction)
	{
		return nullptr;
	}

	for (const auto* Element : InElementsToCheck)
	{
		if(Element)
		{
			InOuter->ProcessEvent(FoundFunction, &Element);
			if (Internal_GetPredicateReturnValue(FoundFunction, Element))
			{
				return Element;
			}
		}
	}

	return nullptr;
}

UObject* UAlgoBPFunctionLibrary::BP_FindByPredicate_Object(UObject* InOuter, const TArray<UObject*>& InElementsToCheck,
	FName InPredicateName)
{
	UFunction* FoundFunction = Internal_FindPredicate(InOuter, InPredicateName);
	if (!FoundFunction)
	{
		return nullptr;
	}

	for (auto* Element : InElementsToCheck)
	{
		if(Element)
		{
			InOuter->ProcessEvent(FoundFunction, &Element);
			if (Internal_GetPredicateReturnValue(FoundFunction, Element))
			{
				return Element;
			}
		}
	}

	return nullptr;
}

TArray<UObject*> UAlgoBPFunctionLibrary::BP_FilterByPredicate_Object(UObject* InOuter,
	const TArray<UObject*>& InElementsToCheck, FName InPredicateName)
{
	/*Could be useful to use TInlineAllocator but in this case we can't*/
	TArray<UObject*> FoundElements;
	UFunction* FoundFunction = Internal_FindPredicate(InOuter, InPredicateName);
	if (!FoundFunction)
	{
		return FoundElements;
	}

	FoundElements.Reserve(InElementsToCheck.Num());
	for (auto* Element : InElementsToCheck)
	{
		if(Element)
		{
			InOuter->ProcessEvent(FoundFunction, &Element);
			if (Internal_GetPredicateReturnValue(FoundFunction, Element))
			{
				FoundElements.Emplace(Element);
			}
		}
	}

	return FoundElements;
}

bool UAlgoBPFunctionLibrary::BP_AllOf_Object(UObject* InOuter, const TArray<UObject*>& InElementsToCheck,
	FName InPredicateName)
{
	UFunction* FoundFunction = Internal_FindPredicate(InOuter, InPredicateName);
	if (!FoundFunction)
	{
		return false;
	}

	for (const auto* Element : InElementsToCheck)
	{
		if(!Element)
		{
			return false;
		}
		
		InOuter->ProcessEvent(FoundFunction, &Element);
		if (!Internal_GetPredicateReturnValue(FoundFunction, Element))
		{
			return false;
		}
	}

	return true;
}

bool UAlgoBPFunctionLibrary::BP_NoneOf_Object(UObject* InOuter, const TArray<UObject*>& InElementsToCheck,
	FName InPredicateName)
{
	UFunction* FoundFunction = Internal_FindPredicate(InOuter, InPredicateName);
	if (!FoundFunction)
	{
		return false;
	}
	
	for (const auto* Element : InElementsToCheck)
	{
		if(Element)
		{
			InOuter->ProcessEvent(FoundFunction, &Element);
			if (Internal_GetPredicateReturnValue(FoundFunction, Element))
			{
				return false;
			}
		}
	}

	return true;
}

bool UAlgoBPFunctionLibrary::BP_AnyOf_Object(UObject* InOuter, const TArray<UObject*>& InElementsToCheck,
	FName InPredicateName)
{
	return !BP_NoneOf_Object(InOuter, InElementsToCheck, InPredicateName);
}

FInstancedStruct UAlgoBPFunctionLibrary::BP_FindByPredicate_Struct(UObject* InOuter,
	TArray<FInstancedStruct> InElementsToCheck, FName InPredicateName)
{
	UFunction* FoundFunction = Internal_FindPredicate(InOuter, InPredicateName);
	if (!FoundFunction)
	{
		return {};
	}

	for (auto& Element : InElementsToCheck)
	{
		InOuter->ProcessEvent(FoundFunction, Element.GetMutableMemory());
		if (Internal_GetPredicateReturnValue(FoundFunction, Element.GetMutableMemory()))
		{
			return Element;
		}
	}

	return {};
}

TArray<FInstancedStruct> UAlgoBPFunctionLibrary::BP_FilterByPredicate_Struct(UObject* InOuter,
	TArray<FInstancedStruct> InElementsToCheck, FName InPredicateName)
{
	/*Could be useful to use TInlineAllocator but in this case we can't*/
	TArray<FInstancedStruct> FoundElements;
	UFunction* FoundFunction = Internal_FindPredicate(InOuter, InPredicateName);
	if (!FoundFunction)
	{
		return FoundElements;
	}

	FoundElements.Reserve(InElementsToCheck.Num());
	for (auto& Element : InElementsToCheck)
	{
		InOuter->ProcessEvent(FoundFunction, Element.GetMutableMemory());
		if (Internal_GetPredicateReturnValue(FoundFunction, Element.GetMutableMemory()))
		{
			FoundElements.Add(Element);
		}
	}

	return FoundElements;
}

bool UAlgoBPFunctionLibrary::BP_AllOf_Struct(UObject* InOuter, TArray<FInstancedStruct> InElementsToCheck,
	FName InPredicateName)
{
	UFunction* FoundFunction = Internal_FindPredicate(InOuter, InPredicateName);
	if (!FoundFunction)
	{
		return false;
	}

	for (auto& Element : InElementsToCheck)
	{
		InOuter->ProcessEvent(FoundFunction, Element.GetMutableMemory());
		if (!Internal_GetPredicateReturnValue(FoundFunction, Element.GetMutableMemory()))
		{
			return false;
		}
	}

	return true;
}

bool UAlgoBPFunctionLibrary::BP_NoneOf_Struct(UObject* InOuter, TArray<FInstancedStruct> InElementsToCheck,
	FName InPredicateName)
{
	UFunction* FoundFunction = Internal_FindPredicate(InOuter, InPredicateName);
	if (!FoundFunction)
	{
		return false;
	}

	for (auto& Element : InElementsToCheck)
	{
		InOuter->ProcessEvent(FoundFunction, Element.GetMutableMemory());
		if (Internal_GetPredicateReturnValue(FoundFunction, Element.GetMutableMemory()))
		{
			return false;
		}
	}

	return true;
}

bool UAlgoBPFunctionLibrary::BP_AnyOf_Struct(UObject* InOuter, TArray<FInstancedStruct> InElementsToCheck,
	FName InPredicateName)
{
	return !BP_NoneOf_Struct(InOuter, InElementsToCheck, InPredicateName);
}

UFunction* UAlgoBPFunctionLibrary::Internal_FindPredicate(UObject* InOuter, const FName& InPredicateName)
{
	if (!InOuter)
	{
#if WITH_EDITOR
		UE_LOG(LogTemp, Warning, TEXT("InOuter passed to FindByPredicate is not valid"));
#endif
		return nullptr;
	}

	if (InPredicateName.IsNone())
	{
#if WITH_EDITOR
		UE_LOG(LogTemp, Warning,
		       TEXT("InFunctionName passed to FindByPredicate is none, no function will be searched"));
#endif
		return nullptr;
	}

	return InOuter->FindFunction(InPredicateName);
}

bool UAlgoBPFunctionLibrary::Internal_GetPredicateReturnValue(const UFunction* InPredicate,
	const void* InPredicateParams)
{
	if(!InPredicate)
	{
		return false;
	}
	
	if(!InPredicateParams)
	{
		return false;
	}
	
	for (TFieldIterator<FProperty> It(InPredicate); It; ++It)
	{
		FProperty* Property = *It;
		if (Property && Property->HasAnyPropertyFlags(CPF_ReturnParm | CPF_OutParm))
		{
			if (const FBoolProperty* ReturnProperty = CastField<FBoolProperty>(Property))
			{
				const bool Value = ReturnProperty->GetPropertyValue_InContainer(InPredicateParams);
				return Value;
			}
		}
	}

	return false;
}
