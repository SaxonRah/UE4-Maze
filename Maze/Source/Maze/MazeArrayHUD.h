// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

/* A rewrite of MazeHUD, using Rama's array code from the thread */
#pragma once


#include "GameFramework/HUD.h"
#include "MazeArrayHUD.generated.h"

USTRUCT()
struct FMazeGridRow
{
    GENERATED_USTRUCT_BODY()

        UPROPERTY()
        TArray<AStaticMeshActor*> Columns;

    void AddNewColumn()
    {
        Columns.Add(NULL);
    }
    //default properties
    FMazeGridRow()
    {

    }
};


USTRUCT()
struct FMazeGrid
{
    GENERATED_USTRUCT_BODY()

        UPROPERTY()
        TArray<FMazeGridRow> Rows;

    void AddNewRow()
    {
        Rows.Add(FMazeGridRow());
    }

    void AddUninitialized(const int32 RowCount, const int32 ColCount)
    {
        //Add Rows
        for (int32 v = 0; v < RowCount; v++)
        {
            AddNewRow();
        }

        //Add Columns
        for (int32 v = 0; v < RowCount; v++)
        {
            for (int32 v = 0; v < ColCount; v++)
            {
                Rows[v].AddNewColumn();
            }
        }
    }

    void Clear()
    {
        if (Rows.Num() <= 0) return;
        //~~~~~~~~~~~~~~~

        //Destroy any walls
        const int32 RowTotal = Rows.Num();
        const int32 ColTotal = Rows[0].Columns.Num();

        for (int32 v = 0; v < RowTotal; v++)
        {
            for (int32 b = 0; b < ColTotal; b++)
            {
                if (Rows[v].Columns[b] && Rows[v].Columns[b]->IsValidLowLevel())
                {
                    Rows[v].Columns[b]->Destroy();
                }
            }
        }

        //Empty
        for (int32 v = 0; v < Rows.Num(); v++)
        {
            Rows[v].Columns.Empty();
        }
        Rows.Empty();
    }
    //default properties
    FMazeGrid()
    {

    }
};

UCLASS()
class AMazeArrayHUD : public AHUD
{
    GENERATED_UCLASS_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MazeHUD)
        bool ShowTests;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MazeGen101isMax)
        float MazeXKeepODD;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MazeGen101isMax)
        float MazeYKeepODD;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = MazeTiles)
        UClass* TileGroundBP;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = MazeTiles)
        UClass* TileBlockBP;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = MazeTiles)
        UClass* TilePillarBP;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = MazeTiles)
        UClass* TileStartBP;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = MazeTiles)
        UClass* TileEndBP;

    //Now you have dynamic array benefits and also UPROPERTY()!
    UPROPERTY()
        FMazeGrid JoyMazeGrid;

    UFUNCTION(BlueprintCallable, Category = MazeGen)
        void GenMaze(float tileX, float tileY);
public:
    virtual void DrawHUD() override;
    virtual void PostInitializeComponents() override;
};

