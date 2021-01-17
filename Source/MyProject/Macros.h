#pragma once


#define COLLISION_CONNECTOR_WALL       ECC_GameTraceChannel2
#define COLLISION_CONNECTOR_FLOOR      ECC_GameTraceChannel4
#define COLLISION_CONNECTOR_ATTACH     ECC_GameTraceChannel5
#define COLLISION_INTERACTABLE         ECC_GameTraceChannel6
#define COLLISION_PANELSIDE            ECC_GameTraceChannel3
#define DEBUGMESSAGE(x, ...) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT(x), __VA_ARGS__));}