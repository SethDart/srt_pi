/******************************************************************************
 * $Id: srt_pi.cpp, v0.1 2012/09/11 SethDart Exp $
 *
 * Project:  OpenCPN
 * Purpose:  SRT Plugin
 * Author:   Jean-Eudes Onfray
 *
 ***************************************************************************
 *   Copyright (C) 2011 by Jean-Eudes Onfray   *
 *   $EMAIL$   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************
 */


#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
  #include "wx/wx.h"
#endif //precompiled headers

#include <typeinfo>
#include "srt_pi.h"
#include "icons.h"

// the class factories, used to create and destroy instances of the PlugIn

extern "C" DECL_EXP opencpn_plugin* create_pi(void *ppimgr)
{
    return new srt_pi(ppimgr);
}

extern "C" DECL_EXP void destroy_pi(opencpn_plugin* p)
{
    delete p;
}




//---------------------------------------------------------------------------------------------------------
//
//    SRT PlugIn Implementation
//
//---------------------------------------------------------------------------------------------------------

srt_pi::srt_pi(void *ppimgr)
      :opencpn_plugin_19(ppimgr)
{
    // Create the PlugIn icons
    initialize_images();
}

int srt_pi::Init(void)
{
    AddLocaleCatalog( _T("opencpn-srt_pi") );

    //    Get a pointer to the opencpn configuration object
    m_pConfig = GetOCPNConfigObject();
    m_pOptionsPage = NULL;

    //    And load the configuration items
    LoadConfig();

    return (
            WANTS_CONFIG              |
            INSTALLS_TOOLBOX_PAGE
            );
}

bool srt_pi::DeInit(void)
{
    /* We must delete remaining page if the plugin is disabled while in Options dialog */
    if ( m_pOptionsPage )
    {
        if ( DeleteOptionsPage( m_pOptionsPage ) )
            m_pOptionsPage = NULL;
        // TODO: else memory leak?
    }
    SaveConfig();
    return true;
}

int srt_pi::GetAPIVersionMajor()
{
    return MY_API_VERSION_MAJOR;
}

int srt_pi::GetAPIVersionMinor()
{
    return MY_API_VERSION_MINOR;
}

int srt_pi::GetPlugInVersionMajor()
{
    return PLUGIN_VERSION_MAJOR;
}

int srt_pi::GetPlugInVersionMinor()
{
    return PLUGIN_VERSION_MINOR;
}

wxBitmap *srt_pi::GetPlugInBitmap()
{
    return _img_srt_pi;
}

wxString srt_pi::GetCommonName()
{
    return _("SRT");
}

wxString srt_pi::GetShortDescription()
{
    return _("SRT AIS class B OEM board configuration plugin for OpenCPN");
}

wxString srt_pi::GetLongDescription()
{
    return _("SRT AIS class B OEM board configuration plugin for OpenCPN\n\
This OEM board is widely used.");
}

void srt_pi::OnSetupOptions(void)
{
    m_pOptionsPage = AddOptionsPage( PI_OPTIONS_PARENT_CONNECTIONS, _("SRT") );
    if (! m_pOptionsPage) {
        wxLogMessage( _T("Error: AddOptionsPage failed!") );
        return;
    }
}

bool srt_pi::LoadConfig(void)
{
    wxFileConfig *pConf = (wxFileConfig *)m_pConfig;

    if(pConf)
    {
        pConf->SetPath( _T("/PlugIns/SRT") );

//        pConf->Read( _T("InputFilename"), &m_ifilename, wxEmptyString );
//        pConf->Read( _T("OutputFilename"), &m_ofilename, wxEmptyString );
//        pConf->Read( _T("Interval"), &m_interval, 1 );

        return true;
    }
    else
        return false;
}

bool srt_pi::SaveConfig(void)
{
    wxFileConfig *pConf = (wxFileConfig *)m_pConfig;

    if(pConf)
    {
        pConf->SetPath( _T("/PlugIns/SRT") );

//        pConf->Write( _T("InputFilename"), m_ifilename );
//        pConf->Write( _T("OutputFilename"), m_ofilename );
//        pConf->Write( _T("Interval"), m_interval );

        return true;
    }
    else
        return false;
}

