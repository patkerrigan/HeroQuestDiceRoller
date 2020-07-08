#pragma once

#include "sfBaseWebService.h"

/**
 * Scene Fusion mock web api handler.
 */
class sfMockWebService : public sfBaseWebService
{
public:
    /**
     * Constructor
     *
     * @param   const FString& - server address
     * @param   const FString& - server port
     */
    sfMockWebService(const FString& host, const FString& port);

    /**
     * Logout
     *
     * @param   OnLogoutDelegate - response handler
     */
    virtual void Logout(OnLogoutDelegate onLogout);

    /**
     * sBaseWebSerive Interface. Email/Password Login
     *
     * @param   const FString& - email address
     * @param   const FString& - password
     * @param   OnLoginDelegate - response handler
     */
    virtual void Login(const FString& email, const FString& pass, OnLoginDelegate onLogin);

    /**
     * sBaseWebSerive Interface. Email/Token Login
     *
     * @param   OnLoginDelegate - response handler
     */
    virtual void Authenticate(OnLoginDelegate onLogin);

    /**
     * sBaseWebSerive Interface. Get Sessions
     *
     * @param   OnGetSessionsDelegate - response handler
     */
    virtual void GetSessions(OnGetSessionsDelegate onGetSessions);

    /**
     * Start Session
     *
     * @param   int - Scene Fusion project ID
     * @param   const FString& - UE level name
     * @param   OnStartSessionDelegate - response handler
     */
    virtual void StartSession(int projectId, const FString& level, OnStartSessionDelegate onStartSession);

    /**
     * sBaseWebSerive Interface. Stop Session
     *
     * @param   TSharedPtr<sfSessionInfo> - session information
     * @param   OnStopSessionDelegate - response handler
     */
    virtual void StopSession(TSharedPtr<sfSessionInfo> sessionInfoPtr, OnStopSessionDelegate onStartSession);

    /**
     * sBaseWebSerive Interface. Set User Color
     *
     * @param   int - Scene Fusion project ID
     * @param   const FLinearColor& - color
     * @param   OnSetUserColorDelegate - response handler
     */
    virtual void SetUserColor(int projectId, const FLinearColor& color, OnSetUserColorDelegate onSetUserColor);

    /**
     * sBaseWebSerive Interface. Refresh Token
     *
     * @param   OnRefreshTokenDelegate - response handler
     */
    virtual void RefreshToken(OnRefreshTokenDelegate onRefreshToken);

    /**
     * Download a LAN server compatible with the current Scene Fusion version
     *
     * @param   TSharedPtr<sfProjectInfo> - project used for authentication
     * @param   OnDownloadLANServerDelegate - download callback
     */
    virtual void DownloadLANServer(TSharedPtr<sfProjectInfo> project, OnDownloadLANServerDelegate callback);

private:
    FString m_host;
    uint16 m_port;
};