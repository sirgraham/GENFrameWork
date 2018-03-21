//------------------------------------------------------------------------------------------
//	DIOLINUXSTREAMBLUETOOTH.CPP
//	
//	LINUX Data IO Stream Bluetooth class
//   
//	Author						: Abraham J. Velez
//	Date Of Creation	: 02/01/2002
//	Last Mofificacion	:	
//
//	GEN  Copyright (C).  All right reserved.		 			 
//------------------------------------------------------------------------------------------
	
	
#if defined(DIO_ACTIVE) && defined(DIOBLUETOOTH_ACTIVE)

//---- INCLUDES ----------------------------------------------------------------------------


#include "XFactory.h"
#include "XDir.h"
#include "XFileTXT.h"
#include "XThreadCollected.h"
#include "XDebug.h"

#include "DIOStreamBluetoothConfig.h"
#include "DIOStreamDeviceBluetooth.h"

#include "DIOLINUXStreamBluetooth.h"

#include "XMemory.h"


//---- GENERAL VARIABLE --------------------------------------------------------------------


//---- CLASS MEMBERS -----------------------------------------------------------------------



/*-------------------------------------------------------------------
//  DIOLINUXSTREAMBLUETOOTH::DIOLINUXSTREAMBLUETOOTH
*/ 
/**
//	
//	
//	@author				Abraham J. Velez
//	@version			18/02/2013 23:17:35
//	
//	@return 			void : 

 
  
*/
/*-----------------------------------------------------------------*/
DIOLINUXSTREAMBLUETOOTH::DIOLINUXSTREAMBLUETOOTH() : DIOSTREAMBLUETOOTH() , XFSMACHINE(0)
{
	Clean();

	AddState(	DIOLINUXBTFSMSTATE_NONE									, 								
				 		DIOLINUXBTFSMEVENT_GETTINGCONNEXION			,	DIOLINUXBTFSMSTATE_GETTINGCONNEXION ,	
						DIOLINUXBTFSMEVENT_CONNECTED						,	DIOLINUXBTFSMSTATE_CONNECTED			 	 ,						
						DIOLINUXBTFSMEVENT_DISCONNECTING				,	DIOLINUXBTFSMSTATE_DISCONNECTING		 ,
						EVENTDEFEND);
	
	AddState(	DIOLINUXBTFSMSTATE_GETTINGCONNEXION			,
						DIOLINUXBTFSMEVENT_CONNECTED						,	DIOLINUXBTFSMSTATE_CONNECTED			 	 ,	
						DIOLINUXBTFSMEVENT_WAITINGTOREAD				,	DIOLINUXBTFSMSTATE_WAITINGTOREAD		 ,
						DIOLINUXBTFSMEVENT_SENDINGDATA					,	DIOLINUXBTFSMSTATE_SENDINGDATA			 ,							
						DIOLINUXBTFSMEVENT_DISCONNECTING				,	DIOLINUXBTFSMSTATE_DISCONNECTING		 ,
						EVENTDEFEND);	

	AddState(	DIOLINUXBTFSMSTATE_CONNECTED						, 												 		
						DIOLINUXBTFSMEVENT_WAITINGTOREAD				,	DIOLINUXBTFSMSTATE_WAITINGTOREAD		 ,
						DIOLINUXBTFSMEVENT_SENDINGDATA					,	DIOLINUXBTFSMSTATE_SENDINGDATA			 ,					
						DIOLINUXBTFSMEVENT_DISCONNECTING				,	DIOLINUXBTFSMSTATE_DISCONNECTING		 ,
						EVENTDEFEND);	

	AddState(	DIOLINUXBTFSMSTATE_WAITINGTOREAD				, 												 		
						DIOLINUXBTFSMEVENT_CONNECTED						,	DIOLINUXBTFSMSTATE_CONNECTED			 	 ,												
						DIOLINUXBTFSMEVENT_SENDINGDATA					,	DIOLINUXBTFSMSTATE_SENDINGDATA			 ,		
						DIOLINUXBTFSMEVENT_DISCONNECTING				,	DIOLINUXBTFSMSTATE_DISCONNECTING		 ,									
						EVENTDEFEND);	

	AddState(	DIOLINUXBTFSMSTATE_DISCONNECTING				, 												 		
						DIOLINUXBTFSMEVENT_GETTINGCONNEXION			,	DIOLINUXBTFSMSTATE_GETTINGCONNEXION ,	
						DIOLINUXBTFSMEVENT_CONNECTED						,	DIOLINUXBTFSMSTATE_CONNECTED			 	 ,						
						DIOLINUXBTFSMEVENT_WAITINGTOREAD				,	DIOLINUXBTFSMSTATE_WAITINGTOREAD		 ,
						DIOLINUXBTFSMEVENT_SENDINGDATA					,	DIOLINUXBTFSMSTATE_SENDINGDATA			 ,											
						EVENTDEFEND);	
						
	threadconnexion = CREATEXTHREAD(XTHREADGROUPID_DIOSTREAMBLUETOOTH, __L("DIOLINUXSTREAMBLUETOOTH::DIOLINUXSTREAMBLUETOOTH"), ThreadRunFunction, (void*)this);
}


//-------------------------------------------------------------------
//  DIOLINUXSTREAMBLUETOOTH::~DIOLINUXSTREAMBLUETOOTH
/**
//
//
//	@author				Abraham J. Velez
//	@version			03/09/2001 16:58:17
//
//	@return 			
*/
//-------------------------------------------------------------------
DIOLINUXSTREAMBLUETOOTH::~DIOLINUXSTREAMBLUETOOTH()
{	    
	if(threadconnexion) 
		{
			threadconnexion->End();
			DELETEXTHREAD(XTHREADGROUPID_DIOSTREAMBLUETOOTH, threadconnexion);
		}
		
	Clean();
}



//-------------------------------------------------------------------
//  DIOLINUXSTREAMBLUETOOTH::Open
/**
//
//
//	@author				Abraham J. Velez
//	@version			03/09/2001 16:58:17
//
//	@return 			bool :
*/
//-------------------------------------------------------------------
bool DIOLINUXSTREAMBLUETOOTH::Open()
{	   
	if(!threadconnexion) return false;
	
	SetEvent(DIOLINUXBTFSMEVENT_GETTINGCONNEXION);	
	status = DIOSTREAMSTATUS_GETTINGCONNEXION;								

	ResetXBuffers();	

	return threadconnexion->Ini();           
}


/*-------------------------------------------------------------------
//  DIOLINUXSTREAMBLUETOOTH::Disconnect
*/ 
/**
//	
//	
//	@author				Abraham J. Velez
//	@version			01/12/2010 23:10:56
//	
//	@return				bool : 
//	*/
/*-----------------------------------------------------------------*/
bool DIOLINUXSTREAMBLUETOOTH::Disconnect()
{	
  if((GetConnectStatus()==DIOSTREAMSTATUS_GETTINGCONNEXION)||
		 (GetConnectStatus()==DIOSTREAMSTATUS_CONNECTED))
		 {
			 SetEvent(DIOLINUXBTFSMEVENT_DISCONNECTING);

			 while(GetConnectStatus()!=DIOSTREAMSTATUS_DISCONNECTED)
				{
					usleep(10000);
				}
		 }

	return true;
}


//-------------------------------------------------------------------
//  DIOLINUXSTREAMBLUETOOTH::Close
/**
//
//
//	@author				Abraham J. Velez
//	@version			03/09/2001 16:58:17
//
//	@return 			
*/
//-------------------------------------------------------------------
bool DIOLINUXSTREAMBLUETOOTH::Close()
{ 
	if(!threadconnexion) return false;
	
	threadconnexion->End();
	
	if(config->IsServer())
		{
			if(sdpserversession) sdp_close((sdp_session_t*)sdpserversession);

			if(handleserver>=0)  
				{
					shutdown(handleserver,SHUT_RDWR);
					close(handleserver);				
					handleserver	= -1;
				}
		}

	if(handlesocket>=0)
		{
      fcntl(handlesocket, F_SETFL, fcntl(handlesocket, F_GETFL,0) & ~O_NONBLOCK);
			shutdown(handlesocket,SHUT_RDWR);
			close(handlesocket);
			handlesocket 	= -1;
		}

	return true;
}




/*-------------------------------------------------------------------
//  DIOLINUXSTREAMBLUETOOTH::IsReadyConnect
*/ 
/**
//	
//	
//	@author				Abraham J. Velez
//	@version			18/05/2013 12:09:04
//	
//	@return 			int : 
//	@param				socket : 
*/
/*-----------------------------------------------------------------*/
int DIOLINUXSTREAMBLUETOOTH::IsReadyConnect(int socket)
{
	struct timeval	tv;
	int							rc;
	fd_set					fdr;
	fd_set					fdw;
	fd_set					fds;

	if(socket==-1) return -1;
								
	FD_ZERO(&fdr);
	FD_ZERO(&fdw);
	FD_ZERO(&fds);

	FD_SET((unsigned int)socket,&fdr);
  FD_SET((unsigned int)socket,&fdw);
	FD_SET((unsigned int)socket,&fds);

	tv.tv_sec  = 0;
	tv.tv_usec = 100;
								
	rc = select(socket+1, &fdr, &fdw, &fds, &tv);
	if(rc==-1) return -1;	
	if(rc== 2) return -1;

  int status1 = FD_ISSET(socket,&fdr) ? 1 : 0;
	int status2 = FD_ISSET(socket,&fdw) ? 1 : 0;
	int status3 = FD_ISSET(socket,&fds) ? 1 : 0;

	if(status3)	return -1;	
	if(((status1) || (status2)) && (rc==1))  return  1;
																																													
	return 0;
}




//-------------------------------------------------------------------
//  DIOLINUXSTREAMBLUETOOTH::SDP_RegisterService
/**
//	
//	
//	@author				Abraham J. Velez
//	@version			08/03/2006 15:36:33
//	
//	@return				sdp_session_t* : 
//	@param				service_name : 
//  @param				service_dsc : 
//  @param				service_prov : 
//  @param				rfcomm_channel :
*/
//-------------------------------------------------------------------
sdp_session_t* DIOLINUXSTREAMBLUETOOTH::SDP_RegisterService(char* service_name,char* service_dsc,char* service_prov,int	rfcomm_channel)
{
  uint32_t service_uuid_int[] = { 0x0111, 10, 1, 1 };
  //uint8_t	 rfcomm_channel			= 1;

  uuid_t root_uuid;
	uuid_t l2cap_uuid;
	uuid_t rfcomm_uuid; 
	uuid_t svc_uuid;

	sdp_list_t* l2cap_list				= 0;
  sdp_list_t* rfcomm_list				= 0;
  sdp_list_t* root_list					= 0;
  sdp_list_t* proto_list				= 0; 
  sdp_list_t* access_proto_list = 0;
  sdp_data_t* channel						= 0;
//sdp_data_t* psm								= 0;

  sdp_record_t record;

	bdaddr_t bdaddr_any		= {0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	bdaddr_t bdaddr_local = {0x00, 0x00, 0x00, 0xff, 0xff, 0xff };
  
  
  sdp_session_t* session = sdp_connect(&bdaddr_any, &bdaddr_local, SDP_RETRY_IF_BUSY);
    
  memset((void *)&record, 0, sizeof(sdp_record_t));
  record.handle = 0xffffffff;

	sdp_uuid16_create(&root_uuid, PUBLIC_BROWSE_GROUP);
  root_list = sdp_list_append(0, &root_uuid);
  sdp_set_browse_groups(&record, root_list );
   
  // set the general service ID
  sdp_uuid128_create( &svc_uuid, &service_uuid_int );
  sdp_set_service_id(&record, svc_uuid );

  // set l2cap information
  sdp_uuid16_create(&l2cap_uuid, L2CAP_UUID);
  l2cap_list = sdp_list_append( 0, &l2cap_uuid );
  proto_list = sdp_list_append( 0, l2cap_list );

  // set rfcomm information
  sdp_uuid16_create(&rfcomm_uuid, RFCOMM_UUID);
  channel			= sdp_data_alloc(SDP_UINT8, &rfcomm_channel);
  rfcomm_list = sdp_list_append( 0, &rfcomm_uuid );
  sdp_list_append( rfcomm_list, channel );
  sdp_list_append( proto_list, rfcomm_list );

  // attach protocol information to service record
  access_proto_list = sdp_list_append( 0, proto_list );
  sdp_set_access_protos( &record, access_proto_list );

  // set the name, provider, and description
  sdp_set_info_attr(&record, service_name, service_prov, service_dsc);

  // connect to the local SDP server, register the service record, and 
  // disconnect  
  sdp_record_register(session, &record, 0);

  // cleanup
  sdp_data_free(channel);
  sdp_list_free(l2cap_list				, 0);
  sdp_list_free(rfcomm_list				, 0);
  sdp_list_free(root_list					, 0);
  sdp_list_free(access_proto_list	, 0);

  return session;  
}



//-------------------------------------------------------------------
//  DIOLINUXSTREAMBLUETOOTH::Clean
/**
//
//
//	@author				Abraham J. Velez
//	@version			03/09/2001 16:58:17
//
//	@return 			
*/
//-------------------------------------------------------------------
void DIOLINUXSTREAMBLUETOOTH::Clean()
{
	threadconnexion		= NULL;
	status 			 			= DIOSTREAMSTATUS_DISCONNECTED;	 
	
	handlesocket 			= -1;
	sdpserversession 	= NULL;
	handleserver			= -1;
}




/*-------------------------------------------------------------------
//	DIOLINUXSTREAMBLUETOOTH::ManagementOfPIN
*/	
/**	
//	
//	
//	
//	@author				Abraham J. Velez
//	@version			26/01/2015 9:37:22
//	
//	@return 			bool : 
//
//  @param				active : 
//  @param				&locMACstring : 
//  @param				&remMACstring : 
//  @param				PIN : 
*/
/*-----------------------------------------------------------------*/
bool DIOLINUXSTREAMBLUETOOTH::ManagementOfPIN(bool active, XSTRING &localMACstring, XSTRING &remoteMACstring, XSTRING& PIN)
{
	XDIR*		xdir;
	XSTRING local;
	XSTRING remote;
	XPATH   xpathfile;
	bool		status = false;;
		
	local  = localMACstring;
	remote = remoteMACstring;

	local.ToUpperCase();
	remote.ToUpperCase();

	//XDEBUG_PRINTCOLOR(1, __L("Local  MAC: %s"), local.Get());
	//XDEBUG_PRINTCOLOR(1, __L("Remote MAC: %s"), remote.Get());

	xpathfile.Format(__L("/var/lib/bluetooth/%s"), local.Get());
	//xpathfile.Format(__L("D:/Projects/pinprobe/%s"), local.Get());
	xpathfile.Slash_Add();

	xdir = xfactory->Create_Dir();
	if(!xdir) return false;
		
	if(!xdir->Exist(xpathfile))
		{
			status = xdir->Make(xpathfile);
		} else status = true;
		
	if(status) 
		{	
			xpathfile += __L("pincodes");
	
			XFILETXT* filetxt = new XFILETXT();
			if(!filetxt) return false;

			status = filetxt->Open(xpathfile, false);
			if(!status) status = filetxt->Create(xpathfile);			
	
			if(status)
				{
					status = filetxt->ReadAllFile();
					if(status)
						{
							int indexfound = XSTRING_NOTFOUND;
							for(int c=0;c<filetxt->GetNLines();c++)
								{
									XSTRING* line = filetxt->GetLine(c);
									if(line)
										{
											int index = line->Find(remote, true);
											if(index!=XSTRING_NOTFOUND) 
												{
													indexfound = c;
													break;
												}
										}
								}

							if(active)							
								{
									if(indexfound != XSTRING_NOTFOUND)
										{
											XSTRING* line = filetxt->GetLine(indexfound);
											if(line) line->Format(__L("%s %s"), remote.Get(), PIN.Get());													
										}
									 else
										{
											XSTRING line;
											line.Format(__L("%s %s"), remote.Get(), PIN.Get());
											filetxt->AddLine(line);
										}

									status = filetxt->WriteAllFile();
								}
							 else 
								{
									filetxt->DeleteLine(indexfound);													
								}

							filetxt->Close();
					
							if(!filetxt->GetNLines()) 
								{
									filetxt->GetPrimaryFile()->Erase(xpathfile);
								}
						}
				}

			delete filetxt;
		}

	xfactory->Delete_Dir(xdir);

	return status;
}






/*-------------------------------------------------------------------
//  DIOLINUXSTREAMBLUETOOTH::ThreadRunFunction
*/ 
/**
//	
//	
//	@author				Abraham J. Velez
//	@version			18/05/2013 12:13:01
//	
//	@return 			void : 
//	@param				param : 
*/
/*-----------------------------------------------------------------*/
void DIOLINUXSTREAMBLUETOOTH::ThreadRunFunction(void* param)
{	  
	DIOLINUXSTREAMBLUETOOTH* diostream = (DIOLINUXSTREAMBLUETOOTH*)param;
	if(!diostream) return;  
                	
	if(diostream->GetEvent()==DIOLINUXBTFSMEVENT_NONE) // No hay nuevos Eventos
		{			
			switch(diostream->GetCurrentState())
				{
					case DIOLINUXBTFSMSTATE_NONE							: break;	

					case DIOLINUXBTFSMSTATE_GETTINGCONNEXION  : switch(diostream->IsReadyConnect(diostream->handlesocket))
																												{
																													case -1: 	{	int				sockerr    = 0;
																																			socklen_t sockerrlen = sizeof(sockerr);
																																																
																																			if(!getsockopt(diostream->handlesocket, SOL_SOCKET, SO_ERROR,(void *)&sockerr, &sockerrlen))
																																				{
																																					if(sockerr==ECONNREFUSED) diostream->SetIsRefusedConnexion(true);																																			
																																				} 

																																			diostream->SetEvent(DIOLINUXBTFSMEVENT_DISCONNECTING);																																																																																					
																																		}
																																		break;
										
																													case  1:	diostream->SetEvent(DIOLINUXBTFSMEVENT_CONNECTED);																	
																																		diostream->status = DIOSTREAMSTATUS_CONNECTED;																																	
																																		break;

																													default:	diostream->status = DIOSTREAMSTATUS_GETTINGCONNEXION;																																																																																																									
																																		break;
																												}																												
																											break;
																										
					case DIOLINUXBTFSMSTATE_CONNECTED				  : break;

					case DIOLINUXBTFSMSTATE_WAITINGTOREAD			: { struct timeval	waitd;
																												fd_set					read_flags;
																												fd_set					write_flags; 
																																																																																																				
																												waitd.tv_sec  = 0;				
																												waitd.tv_usec = 100;		
																											
																												FD_ZERO(&read_flags);			
																												FD_ZERO(&write_flags);																										

																												if(diostream->handlesocket<0)
																													{
																														diostream->SetEvent(DIOLINUXBTFSMEVENT_DISCONNECTING);																														
																														break;
																													}		

																												if(!diostream->IsBlockRead()) FD_SET(diostream->handlesocket, &read_flags);																																																																														
																												if(!diostream->IsBlockWrite())
																													{
																														if(diostream->outbuffer->GetSize()) FD_SET(diostream->handlesocket, &write_flags);
																													}
																											
																												int error = select(diostream->handlesocket+1, &read_flags,&write_flags,(fd_set*)0,&waitd);
																												if(error == -1)
																													{
																														diostream->SetEvent(DIOLINUXBTFSMEVENT_DISCONNECTING);																														
																														break;
																													}			

																												if(FD_ISSET(diostream->handlesocket, &read_flags))  //Socket ready for reading
																													{			      																									
							      																				XBYTE buffer[DIOSTREAM_MAXBUFFER];

																														int size = recv(diostream->handlesocket,(char*)buffer, DIOSTREAM_MAXBUFFER, 0);
																														if(size<=0)
																															{
													      																diostream->SetEvent(DIOLINUXBTFSMEVENT_DISCONNECTING);																																				
																																break;
																															}
																												 		 else diostream->inbuffer->Add(buffer,size);
	      																												
										      																	FD_CLR(diostream->handlesocket, &read_flags);																														
																													}

																												if(FD_ISSET(diostream->handlesocket, &write_flags))  //Socket ready for writing
																													{
																														int esize = diostream->outbuffer->GetSize();
																														if(esize>DIOSTREAM_MAXBUFFER) esize = DIOSTREAM_MAXBUFFER;
																																			
																														if(esize)
																															{																																
																																diostream->outbuffer->SetBlocked(true);
																																int size = send(diostream->handlesocket,(char*)diostream->outbuffer->Get(), esize, 0);
																																diostream->outbuffer->SetBlocked(false);

																																if(size<=0) 
																																	{
																																		diostream->SetEvent(DIOLINUXBTFSMEVENT_DISCONNECTING); 
																																		break;

																																	}	else  diostream->outbuffer->Extract(NULL, 0, size);																														    																										
																															}

																														FD_CLR(diostream->handlesocket, &write_flags);		
																													}
																											}
																											break;

					case DIOLINUXBTFSMSTATE_SENDINGDATA				: break;

					case DIOLINUXBTFSMSTATE_DISCONNECTING			: break;
				}
		}
	 else
		{
			if(diostream->GetEvent()<DIOLINUXBT_LASTEVENT)
				{
					diostream->CheckTransition();

					switch(diostream->GetCurrentState())
						{
							case DIOLINUXBTFSMSTATE_NONE							: break;	

							case DIOLINUXBTFSMSTATE_GETTINGCONNEXION  : {	struct sockaddr_rc  loc_addr = { 0 };
																														struct sockaddr_rc  rem_addr = { 0 }; 								                                           

																														if(diostream->config->IsServer())
																															{				
																																socklen_t	 opt =  sizeof(rem_addr);
		
																																diostream->handleserver = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
																																if(diostream->handleserver < 0) 
																																	{ 
																																		diostream->SetEvent(DIOLINUXBTFSMEVENT_DISCONNECTING);																																																																																																												
																																		break;
																																	}
																																																																																																																
																																loc_addr.rc_family = AF_BLUETOOTH;																																																																															
																																//str2ba(device->GetMAC()->GetOEM(), &loc_addr.rc_bdaddr);
																																loc_addr.rc_channel = (uint8_t) 1;

																																int err;	
																																int port = 1;																															
																																for(port = 1; port <= 31; port++ ) 
																																	{
																																		loc_addr.rc_channel = port;
																																		err = bind(diostream->handleserver, (struct sockaddr *)&loc_addr, sizeof(loc_addr));
																																		if( ! err || errno == EINVAL ) 
																																			{
																																				diostream->SetEvent(DIOLINUXBTFSMEVENT_DISCONNECTING);
																																				break;
																																			}
																																	}		
																													
																																if(port == 31)  
																																	{ 
																																		diostream->SetEvent(DIOLINUXBTFSMEVENT_DISCONNECTING);																																																																				
																																		break;
																																	}																															
																															
																												   			listen(diostream->handleserver, 1);

																																diostream->sdpserversession =(void*)diostream->SDP_RegisterService((char*)diostream->config->GetServerPropertys(0),
											 																																																						 (char*)diostream->config->GetServerPropertys(1),
											 																																																						 (char*)diostream->config->GetServerPropertys(2),port);
																																if(!diostream->sdpserversession) 
																																	{ 
																																		diostream->SetEvent(DIOLINUXBTFSMEVENT_DISCONNECTING);																																																																				
																																		break;
																																	}

																														 															
																																diostream->handlesocket = accept(diostream->handleserver, (struct sockaddr *)&rem_addr, &opt);		

																																fcntl(diostream->handlesocket, F_SETFL, fcntl(diostream->handlesocket, F_GETFL,0) | O_NONBLOCK);																																					
																															}
																														 else
																															{	
																																XSTRING localMACstring;
																																XSTRING remoteMACstring;
																																																																
																																diostream->config->GetLocalMAC()->GetXString(localMACstring);
																																diostream->config->GetRemoteMAC()->GetXString(remoteMACstring);
																																																																																																													
																																diostream->handlesocket = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM); //socket(PF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
																																if(diostream->handlesocket < 0) 
																																	{ 
																																		diostream->SetEvent(DIOLINUXBTFSMEVENT_DISCONNECTING);																																																																																																																							
																																		break;
																																	}
																																																																																																																																					
																																if(diostream->config->GetPIN()->GetSize())
																																	{ 																																		
																																		int				socket_opt = 0;
																																		socklen_t size_opt   = sizeof(socket_opt);

																														        if(getsockopt(diostream->handlesocket, SOL_RFCOMM, RFCOMM_LM, &socket_opt, &size_opt) < 0) 
																																			{
																																				diostream->SetEvent(DIOLINUXBTFSMEVENT_DISCONNECTING);																																																																																																																							
																																				break;	
																																			}
																																		
																																		socket_opt |= (RFCOMM_LM_AUTH | RFCOMM_LM_ENCRYPT);
           
																														        if(socket_opt != 0)
																																			{
																																				if(setsockopt(diostream->handlesocket, SOL_RFCOMM, RFCOMM_LM, &socket_opt, sizeof(socket_opt)) < 0) 
																																					{
																																						diostream->SetEvent(DIOLINUXBTFSMEVENT_DISCONNECTING);																																																																																																																							
																																						break;		
																																					}
																																			}

																																		diostream->ManagementOfPIN(true, localMACstring, remoteMACstring, (*diostream->config->GetPIN()));

																																	} else diostream->ManagementOfPIN(false, localMACstring, remoteMACstring, (*diostream->config->GetPIN()));
																																																																																													

																																loc_addr.rc_family 	= AF_BLUETOOTH;
																																loc_addr.rc_channel = (uint8_t)0;
																																
																																{ 
																																	XSTRING_CREATEOEM(localMACstring, charOEM)	
																																	str2ba(charOEM, &loc_addr.rc_bdaddr);
																																	XSTRING_DELETEOEM(charOEM)	
																																}

																																int error = bind(diostream->handlesocket, (struct sockaddr *)&loc_addr, sizeof(loc_addr));
																																if(error < 0) 
																																	{ 
																																		diostream->SetEvent(DIOLINUXBTFSMEVENT_DISCONNECTING);																																																																																																																							
																																		break;
																																	}
																																																																															  																																																	
																																
																																rem_addr.rc_family = AF_BLUETOOTH;
																																rem_addr.rc_channel = (uint8_t) diostream->config->GetRemoteChannel();
																																
																																{	
																																	XSTRING_CREATEOEM(remoteMACstring, charOEM)	
																																	str2ba(charOEM, &rem_addr.rc_bdaddr);
																																	XSTRING_DELETEOEM(charOEM)	
																																}
																																															
																																diostream->SetIsRefusedConnexion(false);
																																															
																																fcntl(diostream->handlesocket, F_SETFL, fcntl(diostream->handlesocket, F_GETFL,0) | O_NONBLOCK);	                                                                                                                              

																																connect(diostream->handlesocket, (struct sockaddr *)&rem_addr, sizeof(rem_addr));																																
																																																														                                                                                                																																																																																																																																																																																																														
																															}																																															
																													}																					
																													break;

							case DIOLINUXBTFSMSTATE_CONNECTED				  : diostream->SetEvent(DIOLINUXBTFSMEVENT_WAITINGTOREAD); 
																													break;

							case DIOLINUXBTFSMSTATE_WAITINGTOREAD			: break;

							case DIOLINUXBTFSMSTATE_SENDINGDATA				: break;

							case DIOLINUXBTFSMSTATE_DISCONNECTING			: if(diostream->config->GetPIN()->GetSize())
																														{
																															XSTRING localMACstring;
																															XSTRING remoteMACstring;
																																																																
																															diostream->config->GetLocalMAC()->GetXString(localMACstring);
																															diostream->config->GetRemoteMAC()->GetXString(remoteMACstring);
																																																																																																																																											
																															diostream->ManagementOfPIN(false, localMACstring, remoteMACstring, (*diostream->config->GetPIN()));																																																																																																																																				
																														}
								
																													diostream->threadconnexion->Run(false);
																													diostream->status = DIOSTREAMSTATUS_DISCONNECTED;
																													break;
						}
				}
		}
}

#endif
