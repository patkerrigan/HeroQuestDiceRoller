#pragma once

#include "ksRoomInfo.h"
#include <CoreMinimal.h>
#include <Misc/DateTime.h>

using namespace KS::Reactor;

/**
 * Session data that is available without connecting to a room. Consists of room info and level creator.
 */
struct sfSessionInfo
{
public:
    int ProjectId;
    FString ProjectName;
    FString Creator;
    FString UnrealProjectName;
    FString LevelName;
    FString LaunchApplication;
    bool CanStop;
    FString RequiredVersion;
    ksRoomInfo::SPtr RoomInfoPtr;
    FDateTime Time;
    FDateTime StartTime;

    /**
     * Constructor
     */
    sfSessionInfo();

    /**
     * Overload the == operator.
     *
     * @param   const sfSessionInfo& sessionInfo
     * @return  bool
     */
    bool operator==(const sfSessionInfo& sessionInfo) {
        return ProjectId == sessionInfo.ProjectId &&
            ProjectName == sessionInfo.ProjectName &&
            Creator == sessionInfo.Creator &&
            LevelName == sessionInfo.LevelName &&
            LaunchApplication == sessionInfo.LaunchApplication &&
            CanStop == sessionInfo.CanStop &&
            RequiredVersion == sessionInfo.RequiredVersion &&
            *RoomInfoPtr == *sessionInfo.RoomInfoPtr;
    }

    /**
     * Overload the != operator.
     *
     * @param   const sfSessionInfo& sessionInfo
     * @return  bool
     */
    bool operator!=(const sfSessionInfo& sessionInfo) {
        return !(*this == sessionInfo);
    }
};