#include <iostream>
#include "ChainOfResponsibility.h"
int main()
{
    AddIngredientHandler* hand1 = new AddIngredientHandler();
    AddRecipeHandler* hand2 = new AddRecipeHandler();
    CreateRecipeHandler* hand3 = new CreateRecipeHandler();
    hand1->setNextHandler(hand2)->setNextHandler(hand3);
    hand1->handleRequest("CreateRecipeRequest");
    return 0;
}
