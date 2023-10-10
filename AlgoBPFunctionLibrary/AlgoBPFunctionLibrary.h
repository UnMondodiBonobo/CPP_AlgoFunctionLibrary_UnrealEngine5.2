// Free to use WIP AlgoBPFunctionLibrary, October 8 2023, Alessandro Profera

#pragma once

#include <CoreMinimal.h>
#include <Kismet/BlueprintFunctionLibrary.h>
#include "AlgoBPFunctionLibrary.generated.h"

UCLASS()
class ALGO_API UAlgoBPFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	//////////////////////////////    UObject Utilities   //////////////////////////////////////

	/**
	 * @brief FindByPredicate on UObject Array, Predicate function must be implemented in passed
	 * Outer Object and must manipulate bIsSatisfiedPred in order to satisfy the predicate
	 *
	 * @param InOuter Outer Object in which the predicate is defined
	 * @param InElementsToCheck Array Elements to check
	 * @param InPredicateName Predicate Name to search for in the Outer Object Map functions list
	 */
public:
	UFUNCTION(BlueprintCallable, Category = "Predicate Blueprint Functions",
		DisplayName = "FindByPredicate_ConstObject",
		meta = (DefaultToSelf = "InOuter"))
	static UPARAM(DisplayName = "Found UObject") const UObject* BP_FindByPredicate_ConstObject(UObject* InOuter,
		const TArray<UObject*>& InElementsToCheck,
		FName InPredicateName);

	UFUNCTION(BlueprintCallable, Category = "Predicate Blueprint Functions", DisplayName = "FindByPredicate_Object",
		meta = (DefaultToSelf = "InOuter"))
	static UPARAM(DisplayName = "Found UObject") UObject* BP_FindByPredicate_Object(UObject* InOuter,
		const TArray<UObject*>& InElementsToCheck,
		FName InPredicateName);

	UFUNCTION(BlueprintCallable, Category = "Predicate Blueprint Functions",
		DisplayName = "FilterByPredicate_UObject",
		meta = (DefaultToSelf = "InOuter"))
	static UPARAM(DisplayName = "Found UObjects") TArray<UObject*> BP_FilterByPredicate_Object(
		UObject* InOuter,
		const TArray<UObject*>& InElementsToCheck,
		FName InPredicateName);

	UFUNCTION(BlueprintCallable, Category = "Predicate Blueprint Functions", DisplayName = "AllOf_Object",
		meta = (DefaultToSelf = "InOuter"))
	static bool BP_AllOf_Object(UObject* InOuter,
		const TArray<UObject*>& InElementsToCheck,
		FName InPredicateName);

	UFUNCTION(BlueprintCallable, Category = "Predicate Blueprint Functions", DisplayName = "NoneOf_Object",
		meta = (DefaultToSelf = "InOuter"))
	static bool BP_NoneOf_Object(UObject* InOuter,
		const TArray<UObject*>& InElementsToCheck,
		FName InPredicateName);

	UFUNCTION(BlueprintCallable, Category = "Predicate Blueprint Functions", DisplayName = "AnyOf_Object",
		meta = (DefaultToSelf = "InOuter"))
	static bool BP_AnyOf_Object(UObject* InOuter,
		const TArray<UObject*>& InElementsToCheck,
		FName InPredicateName);


	//////////////////////////////    Struct Utilities   //////////////////////////////////////
	/// Available from Unreal Engine version 5.2 and beyond, StructUtils experimental plugin must be enabled ///

	UFUNCTION(BlueprintCallable, Category = "Predicate Blueprint Functions", DisplayName = "FindByPredicate_Structure",
		meta = (DefaultToSelf = "InOuter"))
	static UPARAM(DisplayName = "Found Instanced Struct") FInstancedStruct BP_FindByPredicate_Struct(UObject* InOuter,
		TArray<FInstancedStruct> InElementsToCheck,
		FName InPredicateName);

	UFUNCTION(BlueprintCallable, Category = "Predicate Blueprint Functions",
		DisplayName = "FilterByPredicate_Structure",
		meta = (DefaultToSelf = "InOuter"))
	static UPARAM(DisplayName = "Found Instanced Struct Array") TArray<FInstancedStruct> BP_FilterByPredicate_Struct(
		UObject* InOuter,
		TArray<FInstancedStruct> InElementsToCheck,
		FName InPredicateName);

	UFUNCTION(BlueprintCallable, Category = "Predicate Blueprint Functions", DisplayName = "AllOf_Structure",
		meta = (DefaultToSelf = "InOuter"))
	static bool BP_AllOf_Struct(UObject* InOuter,
		TArray<FInstancedStruct> InElementsToCheck,
		FName InPredicateName);

	UFUNCTION(BlueprintCallable, Category = "Predicate Blueprint Functions", DisplayName = "NoneOf_Structure",
		meta = (DefaultToSelf = "InOuter"))
	static bool BP_NoneOf_Struct(UObject* InOuter,
		TArray<FInstancedStruct> InElementsToCheck,
		FName InPredicateName);

	UFUNCTION(BlueprintCallable, Category = "Predicate Blueprint Functions", DisplayName = "AnyOf_Structure",
		meta = (DefaultToSelf = "InOuter"))
	static bool BP_AnyOf_Struct(UObject* InOuter,
		TArray<FInstancedStruct> InElementsToCheck,
		FName InPredicateName);

	/*Internal utility methods*/
private:
	static UFunction* Internal_FindPredicate(UObject* InOuter, const FName& InPredicateName);
	static bool Internal_GetPredicateReturnValue(const UFunction* InPredicate, const void* InPredicateParams);
};
