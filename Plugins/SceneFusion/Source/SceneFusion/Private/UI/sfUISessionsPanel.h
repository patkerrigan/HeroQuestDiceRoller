#pragma once

#include "sfUIPanel.h"
#include "../../Public/sfProjectInfo.h"
#include "../../Public/sfSessionInfo.h"
#include <Runtime/Slate/Public/Framework/SlateDelegates.h>
#include <Widgets/Views/SListView.h>
#include <Widgets/Input/SComboBox.h>
#include <Widgets/Input/SEditableTextBox.h>
#include <Runtime/Networking/Public/Common/UdpSocketReceiver.h>
#include <Runtime/Networking/Public/Common/UdpSocketBuilder.h>
#include <Runtime/Networking/Public/Networking.h>

/**
 * Scene Fusion sessions list
 */
class sfUISessionsPanel : public sfUIPanel
{
public:
    /**
     * Delegate for UI logout
     */
    DECLARE_DELEGATE(OnLogoutDelegate);

    /**
     * Delegate for join/start sessions
     *
     * @param    TSharedPtr<sfSessionInfo> - session information
     */
    DECLARE_DELEGATE_OneParam(OnJoinSessionDelegate, TSharedPtr<sfSessionInfo>);

    /**
     * Constructor
     */
    sfUISessionsPanel();

    /**
     * Destructor
     */
    virtual ~sfUISessionsPanel();

    /**
     * Show the UI widget
     */
    virtual void Show() override;
    virtual void Hide() override;

    /**
     * Shows the download link for the newest version of Scene Fusion.
     */
    void ShowDownloadLink();

    /**
     * Hides the download link for the newest version of Scene Fusion.
     */
    void HideDownloadLink();

    /**
     * Logout event handler
     */
    OnLogoutDelegate OnLogout;

    /**
     * Join session event handler
     */
    OnJoinSessionDelegate OnJoinSession;

    /**
     * Start session event handler
     */
    OnJoinSessionDelegate OnStartSession;

private:
    /**
     * Version check results
     */
    enum ServerState
    {
        OK,
        MISSING,
        INCOMPATIBLE
    };

    // UI widgets
    TSharedPtr<SComboBox<TSharedPtr<FString>>> m_accountComboPtr;
    TSharedPtr<SComboBox<TSharedPtr<sfProjectInfo>>> m_projectComboPtr;
    TSharedPtr<SListView<TSharedPtr<sfSessionInfo>>> m_sessionListPtr;
    TSharedPtr<STextBlock> m_selectedAccountPtr;
    TSharedPtr<STextBlock> m_selectedProjectPtr;
    TSharedPtr<sfUIMessageBox> m_newVersionPtr;
    TSharedPtr<sfUIMessageBox> m_limitMessagePtr;

    // Session Data
    int m_projectId;
    int m_objectLimit;
    TArray<TSharedPtr<FString>> m_accounts;
    TArray<TSharedPtr<sfProjectInfo>> m_projects;
    TArray<TSharedPtr<sfSessionInfo>> m_sessions;
    TArray<TSharedPtr<sfSessionInfo>> m_lanSessions;
    TMap<uint32, TSharedPtr<sfSessionInfo>> m_lanSessionMap;
    ProjectMap m_projectMap;

    //LAN
    TSharedPtr<SListView<TSharedPtr<sfSessionInfo>>> m_lanSessionListPtr;
    TSharedPtr<SEditableTextBox> m_portPtr;
    TSharedPtr<SEditableTextBox> m_manualAddressPtr;
    TSharedPtr<SEditableTextBox> m_manualPortPtr;
    FProcHandle m_processHandle;
    FUdpSocketReceiver* m_socketReceiverPtr;
    FSocket* m_socket;
    ServerState m_lanServerState;

    TSet<uint32_t> m_stoppingRoomIds;

    /**
     * Send a web request to join a sesssion
     *
     * @param   TSharedPtr<sfSessionInfo> sessionPtr
     */
    void JoinSession(TSharedPtr<sfSessionInfo> sessionPtr);

    /**
     * Handle a select account/logout UI action
     *
     * @param   TSharedPtr<FString> - account name
     * @param   ESelectInfo::Type - selection type
     */
    void SelectAccount(TSharedPtr<FString> valuePtr, ESelectInfo::Type selectType);

    /**
     * Handle a select account/logout UI action
     *
     * @param   TSharedPtr<sfProjectInfo> - project information
     * @param   ESelectInfo::Type - selection type
     */
    void SelectProject(TSharedPtr<sfProjectInfo> valuePtr, ESelectInfo::Type selectType);

    /**
     * Send a web request to start a new session
     *
     * @return  FReply - UI event reply
     */
    FReply StartSession();

    /**
     * Handle the reply from a StartSession web request.
     *
     * @param   TSharedPtr<sfSessionInfo> - session information
     * @param   const FString& - error message
     */
    void StartSessionReply(TSharedPtr<sfSessionInfo> sessionInfoPtr, const FString& error);

    /**
     * Send a web request to stop a sesssion
     *
     * @param   TSharedPtr<sfSessionInfo> sessionPtr
     */
    void StopSession(TSharedPtr<sfSessionInfo> sessionPtr);

    /**
     * Called when a stop session attempt completes.
     *
     * @param   TSharedPtr<sfSessionInfo> sessionInfoPtr - session information
     * @param   const FString& errorMessage. Empty string if the connection was successful.
     */
    void StopSessionReply(TSharedPtr<sfSessionInfo> sessionInfoPtr, const FString& errorMessage);

    /**
     * Handle the reply from a GetSessions web request
     *
     * @param   ProjectMap& - project information
     * @param   const FString& - error message
     */
    void GetSessionsReply(ProjectMap& projectMap, const FString& error);

    /**
     * Handle the reply from a DownloadLANServer web request
     *
     * @param   TArray<uint8> data
     * @param   FString& - error message
     */
    void DownloadLANServerReply(TArray<uint8> data, FString& error);

    /**
     * Redraw the session list
     */
    void RedrawSessionsList();

    /**
     * UI for account info.
     */
    void AccountInfoArea();

    /**
     * UI for online sessions.
     */
    void OnlineArea();

    /**
     * UI for LAN sessions.
     */
    void LANArea();

    /**
     * Start a LAN session.
     * 
     * @return  FReply
     */
    FReply StartLANSession();

    /**
     * Install the Scene Fusion LAN server.
     *
     * @return  FReply
     */
    FReply InstallLANServer();

    /**
     * Check that a local SF server exists and that it is compatible with the current SF version
     *
     * @return ServerState
     */
    static ServerState ServerCheck();

    /**
     * Initialize a UDP socket used to receive SF LAN server broadcasts.
     */
    void InitializeUDP();

    /**
     * Cleanup the UDP sockets used to receive SF LAN server broadcasts.
     */
    void CleanupUDP();

    /**
     * Handle the reception of a UDP broadcast
     *
     * @param   const FArrayReaderPtr& - UDP packet data
     * @param   const FIPv4Endpoint& - UDP packet sender endpoint info
     */
    void OnBroadcastRecieved(const FArrayReaderPtr& ArrayReaderPtr, const FIPv4Endpoint& EndPt);

    /**
     * Manually connect to a session.
     * 
     * @return  FReply
     */
    FReply ManualConnect();
};