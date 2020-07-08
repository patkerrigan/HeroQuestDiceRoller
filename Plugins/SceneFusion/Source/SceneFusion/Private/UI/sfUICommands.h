#pragma once

#include <CoreMinimal.h>
#include <Framework/Commands/Commands.h>

/**
 * Scene Fusion UI command list
 */
class sfUICommands : public TCommands<sfUICommands>
{
public:
    // Constructor
    sfUICommands();

    // TCommands<> interface
    virtual void RegisterCommands() override;

    // Commands
    TSharedPtr<FUICommandInfo> ToolBarClickPtr;
    TSharedPtr<FUICommandInfo> MissingAssetsPtr;
    TSharedPtr<FUICommandInfo> GettingStartedPtr;
    TSharedPtr<FUICommandInfo> WebConsolePtr;
    TSharedPtr<FUICommandInfo> DocumentPtr;
    TSharedPtr<FUICommandInfo> EmailSupportPtr;
};