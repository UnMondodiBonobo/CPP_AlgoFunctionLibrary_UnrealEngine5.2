# CPP_AlgoFunctionLibrary_UnrealEngine5.2
Blueprint Function Library in C++ that implements some Algo c++ functionalities in Blueprint nodes like FindByPredicate, FilterByPredicate, AllOf, NoneOf, AnyOf

AlgoBPFunctionLibrary is a function library that implements C++ Unreal FindByPredicate, 
FilterByPredicate, AllOf, NoneOf, AnyOf as blueprint nodes on all UObjects and on Structs 
(StructUtils plugin must be enabled -UnrealEngine 5.2 and beyond-).

Implementation:

  1. It behaves like the methods listed above: a predicate needs to be defined inside the 
Object that calls these nodes and passed to the Algo node as lvalue or rvalue, the 
predicate also must return a boolean value as if it is the return value of C++lambdas.

  3. The Algo node processes the UFunction found on the Object passed as Outer Object 
and executes it. After every execution loop, it searches for the return value inside 
the properties of the function passed and executes the core functionality (add to 
array for FilterByPredicate, return the element for FindByPredicate, etc) if the
predicate is satisfied.
