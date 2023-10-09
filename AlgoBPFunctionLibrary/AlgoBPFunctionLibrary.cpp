// Free to use WIP AlgoBPFunctionLibrary, October 8 2023, Alessandro Profera

#include "AlgoBPFunctionLibrary.h"
#include <InstancedStruct.h>

const UObject* UAlgoBPFunctionLibrary::BP_FindByPredicate_ConstObject(UObject* InOuter, const TArray<UObject*>& InElementsToCheck,
	bool& bIsPredSatisfied, const FName& InPredicateName)
{
	UFunction* FoundFunction = Internal_FindPredicate(InOuter, InPredicateName);
	if (!FoundFunction)
	{
		return {};
	}
	
	bIsPredSatisfied = false;
	for (const auto* Element : InElementsToCheck)
	{
		if(!Element)
		{
			continue;	
		}
		
		InOuter->ProcessEvent(FoundFunction, &Element);
		if (bIsPredSatisfied)
		{
			return Element;
		}
	}

	return nullptr;
}

UObject* UAlgoBPFunctionLibrary::BP_FindByPredicate_Object(UObject* InOuter, TArray<UObject*>& InElementsToCheck,
	bool& bIsPredSatisfied, const FName& InPredicateName)
{
	UFunction* FoundFunction = Internal_FindPredicate(InOuter, InPredicateName);
	if (!FoundFunction)
	{
		return {};
	}
	
	bIsPredSatisfied = false;
	for (const auto& Element : InElementsToCheck)
	{
		InOuter->ProcessEvent(FoundFunction, Element);
		if (bIsPredSatisfied)
		{
			return Element;
		}
	}

	return nullptr;
}

TArray<UObject*> UAlgoBPFunctionLibrary::BP_FilterByPredicate_Object(UObject* InOuter,
	const TArray<UObject*>& InElementsToCheck, bool& bIsPredSatisfied, const FName& InPredicateName)
{
	UFunction* FoundFunction = Internal_FindPredicate(InOuter, InPredicateName);
	if (!FoundFunction)
	{
		return {};
	}
	
	bIsPredSatisfied = false;
	/*Could be useful to use TInlineAllocator but in this case we can't*/
	TArray<UObject*> FoundElements;
	FoundElements.Reserve(InElementsToCheck.Num());
	for (const auto& Element : InElementsToCheck)
	{
		InOuter->ProcessEvent(FoundFunction, Element);
		if (bIsPredSatisfied)
		{
			FoundElements.Emplace(Element);
		}
	}

	return FoundElements;
}


bool UAlgoBPFunctionLibrary::BP_AllOf_Object(UObject* InOuter, const TArray<UObject*>& InElementsToCheck,
	bool& bIsPredSatisfied, const FName& InPredicateName)
{
	UFunction* FoundFunction = Internal_FindPredicate(InOuter, InPredicateName);
	if (!FoundFunction)
	{
		return false;
	}
	
	bIsPredSatisfied = false;
	for (const auto& Element : InElementsToCheck)
	{
		InOuter->ProcessEvent(FoundFunction, Element);
		if (!bIsPredSatisfied)
		{
			return false;
		}
	}

	return true;
}

bool UAlgoBPFunctionLibrary::BP_NoneOf_Object(UObject* InOuter, const TArray<UObject*>& InElementsToCheck,
	bool& bIsPredSatisfied, const FName& InPredicateName)
{
	UFunction* FoundFunction = Internal_FindPredicate(InOuter, InPredicateName);
	if (!FoundFunction)
	{
		return false;
	}
	
	bIsPredSatisfied = false;
	for (const auto& Element : InElementsToCheck)
	{
		InOuter->ProcessEvent(FoundFunction, Element);
		if (bIsPredSatisfied)
		{
			return false;
		}
	}

	return true;
}

bool UAlgoBPFunctionLibrary::BP_AnyOf_Object(UObject* InOuter, const TArray<UObject*>& InElementsToCheck,
	bool& bIsPredSatisfied, const FName& InPredicateName)
{
	return !BP_NoneOf_Object(InOuter, InElementsToCheck, bIsPredSatisfied, InPredicateName);
}

FInstancedStruct UAlgoBPFunctionLibrary::BP_FindByPredicate_Struct(UObject* InOuter,
	TArray<FInstancedStruct> InElementsToCheck, bool& bIsPredSatisfied, const FName& InPredicateName)
{
	UFunction* FoundFunction = Internal_FindPredicate(InOuter, InPredicateName);
	if (!FoundFunction)
	{
		return {};
	}

	bIsPredSatisfied = false;
	for (const auto& Element : InElementsToCheck)
	{
		InOuter->ProcessEvent(FoundFunction, (void*)Element.GetMemory());
		if (bIsPredSatisfied)
		{
			return Element;
		}
	}

	return {};
}

TArray<FInstancedStruct> UAlgoBPFunctionLibrary::BP_FilterByPredicate_Struct(UObject* InOuter,
	TArray<FInstancedStruct> InElementsToCheck, bool& bIsPredSatisfied, const FName& InPredicateName)
{
	UFunction* FoundFunction = Internal_FindPredicate(InOuter, InPredicateName);
	if (!FoundFunction)
	{
		return {};
	}

	bIsPredSatisfied = false;
	
	/*Could be useful to use TInlineAllocator but in this case we can't*/
	TArray<FInstancedStruct> FoundElements;
	FoundElements.Reserve(InElementsToCheck.Num());
	for (const auto& Element : InElementsToCheck)
	{
		InOuter->ProcessEvent(FoundFunction, (void*)Element.GetMemory());
		if (bIsPredSatisfied)
		{
			FoundElements.Add(Element);
		}
	}

	return FoundElements;
}

bool UAlgoBPFunctionLibrary::BP_AllOf_Struct(UObject* InOuter, TArray<FInstancedStruct> InElementsToCheck,
	bool& bIsPredSatisfied, const FName& InPredicateName)
{
	UFunction* FoundFunction = Internal_FindPredicate(InOuter, InPredicateName);
	if (!FoundFunction)
	{
		return false;
	}

	bIsPredSatisfied = false;
	for (const auto& Element : InElementsToCheck)
	{
		InOuter->ProcessEvent(FoundFunction, (void*)Element.GetMemory());
		if (!bIsPredSatisfied)
		{
			return false;
		}
	}

	return true;
}

bool UAlgoBPFunctionLibrary::BP_NoneOf_Struct(UObject* InOuter, TArray<FInstancedStruct> InElementsToCheck,
	bool& bIsPredSatisfied, const FName& InPredicateName)
{
	UFunction* FoundFunction = Internal_FindPredicate(InOuter, InPredicateName);
	if (!FoundFunction)
	{
		return false;
	}

	bIsPredSatisfied = false;
	for (const auto& Element : InElementsToCheck)
	{
		InOuter->ProcessEvent(FoundFunction, (void*)Element.GetMemory());
		if (bIsPredSatisfied)
		{
			return false;
		}
	}

	return true;
}

bool UAlgoBPFunctionLibrary::BP_AnyOf_Struct(UObject* InOuter, TArray<FInstancedStruct> InElementsToCheck,
	bool& bIsPredSatisfied, const FName& InPredicateName)
{
	return !BP_NoneOf_Struct(InOuter, InElementsToCheck, bIsPredSatisfied, InPredicateName);
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
