#pragma once
#include <iostream>
#include <string>

// Handler interface
class Handler {
protected:
    Handler* nextHandler = 0;
public:
    virtual void handleRequest(const std::string& request) = 0;
    virtual Handler* setNextHandler(Handler* nextHandler) = 0;
};

// Concrete handler 
class AddIngredientHandler : public Handler {
public:
    AddIngredientHandler(){
        nextHandler = nullptr;
    }

    void handleRequest(const std::string& request) {
        if (request == "AddIngredientRequest") {
            std::cout << "AddIngredientRequest: Handling the request..." << std::endl;
        }
        else if (nextHandler != nullptr) {
            std::cout << "AddIngredientRequest: Unable to handle the request. Passing it to the next handler." << std::endl;
            nextHandler->handleRequest(request);
        }
        else {
            std::cout << "AddIngredientRequest: End of the chain. Unable to handle the request." << std::endl;
        }
    }

    Handler* setNextHandler(Handler* handler) {
        nextHandler = handler;
        return handler;
    }
};

// Concrete handler
class AddRecipeHandler : public Handler {

public:
    AddRecipeHandler() {
        nextHandler = nullptr;
    }

    void handleRequest(const std::string& request) {
        if (request == "AddRecipeRequest") {
            std::cout << "AddRecipeRequest: Handling the request..." << std::endl;
        }
        else if (nextHandler != nullptr) {
            std::cout << "AddRecipeRequest: Unable to handle the request. Passing it to the next handler." << std::endl;
            nextHandler->handleRequest(request);
        }
        else {
            std::cout << "AddRecipeRequest: End of the chain. Unable to handle the request." << std::endl;
        }
    }

    Handler* setNextHandler(Handler* handler) {
        nextHandler = handler;
        return handler;
    }
};


class CreateRecipeHandler : public Handler{
public:
    CreateRecipeHandler() {
        nextHandler = nullptr;
    }

    Handler* setNextHandler(Handler* handler) {
        nextHandler = handler;
        return handler;
    }

    void handleRequest(const std::string& request) {
        if (request == "CreateRecipeRequest") {
            std::cout << "CreateRecipeRequest: Handling request..." << std::endl;
        }
        else if (nextHandler != nullptr){
            std::cout << "CreateRecipeRequest: Unable to handle request. Passing it to the next handler." << std::endl;
            nextHandler->handleRequest(request);
        }
        else {
            std::cout << "CreateRecipeRequest: End of the chain. Unable to handle request." << std::endl;
        }
    }
};
