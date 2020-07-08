#pragma once

#include "sfUIMessageBox.h"

#include <CoreMinimal.h>
#include <Widgets/Layout/SScrollBox.h>
#include <Widgets/SBoxPanel.h>
#include <Widgets/Text/STextBlock.h>

/**
 * Scene Fusion UI panel
 */
class sfUIPanel : public TSharedFromThis<sfUIPanel>
{
public:
    /**
     * Constructor
     *
     * @param   const FString& - title
     */
    sfUIPanel(const FString& title);

    /**
     * Destructor
     */
    virtual ~sfUIPanel() {}

    /**
     * Get the UI widget
     *
     * @return  TSharedRef<SScrollBox> - UI widget
     */
    TSharedRef<SScrollBox> Widget();

    /**
     * Show the UI widget
     */
    virtual void Show();

    /**
     * Hide the UI widget
     */
    virtual void Hide();

    /**
     * Enable the UI
     */
    virtual void Enable();

    /**
     * Disable the UI
     */
    virtual void Disable();

    /**
     * Display a message at the bottom of this panel.
     *
     * @param   const FString& - message
     * @param   sfUIMessageBox::Icon - message icon (INFO, ERROR, WARNING)
     * @param   sfUIMessageBox::OnClicDelegate - if provided, will show a "Details" button that calls this function
     *          when clicked.
     */
    virtual void DisplayMessage(
        const FString& error,
        sfUIMessageBox::Icon icon, 
        sfUIMessageBox::OnClickDelegate onClick = nullptr);

    /**
     * Clears the message at the bottom of this panel.
     */
    virtual void ClearMessage();

protected:
    TSharedPtr<SScrollBox> m_widgetPtr;
    TSharedPtr<STextBlock> m_titlePtr;
    TSharedPtr<SVerticalBox> m_contentPtr;
    TSharedPtr<sfUIMessageBox> m_msgPtr;
};