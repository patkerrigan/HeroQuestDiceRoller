#pragma once

#include "sfSessionInfo.h"
#include <CoreMinimal.h>

/**
 * Scene Fusion project information.  Includes limits and a list of running sessions.
 */
struct sfProjectInfo
{
public:
    int Id;
    FString Name;
    int CompanyId;
    FString CompanyName;
    FString SubscriptionId;
    FString SubscriptionName;
    int SessionLimit;
    int UserLimit;
    int ObjectLimit;
    int SessionCount;
    int UserCount;
    FDateTime SubscriptionExpiry;
    TArray<TSharedPtr<sfSessionInfo>> Sessions;
    bool LANEnabled;

    /**
     * Constructor
     */
    sfProjectInfo() :
        Id{ -1 },
        Name{ "" },
        CompanyId{ -1 },
        CompanyName{ "" },
        SubscriptionId{ "" },
        SubscriptionName{ "" },
        SessionLimit{ -1 },
        UserLimit{ 2 },
        ObjectLimit{ 0 },
        SessionCount{ 0 },
        UserCount{ 0 },
        LANEnabled{ false }
    {
    }

    /**
     * Overload the == operator.
     *
     * @param   const sfProjectInfo& projectInfo
     * @return  bool
     */
    bool operator==(const sfProjectInfo& projectInfo) {
        if (Id != projectInfo.Id ||
            Name != projectInfo.Name ||
            CompanyId != projectInfo.CompanyId ||
            CompanyName != projectInfo.CompanyName ||
            SubscriptionId != projectInfo.SubscriptionId ||
            SubscriptionName != projectInfo.SubscriptionName || 
            SessionLimit != projectInfo.SessionLimit ||
            UserLimit != projectInfo.UserLimit ||
            ObjectLimit != projectInfo.ObjectLimit ||
            SessionCount != projectInfo.SessionCount ||
            UserCount != projectInfo.UserCount ||
            SubscriptionExpiry != projectInfo.SubscriptionExpiry ||
            Sessions.Num() != projectInfo.Sessions.Num() ||
            LANEnabled != projectInfo.LANEnabled)
        {
            return false;
        }
        for (TSharedPtr<sfSessionInfo> a : Sessions)
        {
            for (TSharedPtr<sfSessionInfo> b : projectInfo.Sessions)
            {
                if (*a != *b)
                {
                    return false;
                }
            }
        }
        return true;
    }

    /**
     * Overload the != operator.
     *
     * @param   const sfProjectInfo& projectInfo
     * @return  bool
     */
    bool operator!=(const sfProjectInfo& projectInfo) {
        return !(*this == projectInfo);
    }
};

typedef TMap<int, TSharedPtr<sfProjectInfo>> ProjectMap;
