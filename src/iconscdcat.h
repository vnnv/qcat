/***************************************************************************
 *   Copyright (C) 2007-2011 by Victor Nikiforov                           *
 *   victor.nike@gmail.com                                                 *
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
 ***************************************************************************/

#ifndef ICONBASE_H_CDCAT
#define ICONBASE_H_CDCAT

class QPixmap;

void      init_icon_base(void);
QPixmap * get_m_catalog_icon(void);
QPixmap * get_m_unknown_icon(void);
QPixmap * get_m_cd_icon(void);
QPixmap * get_m_dvd_icon(void);
QPixmap * get_m_hdd_icon(void);
QPixmap * get_m_net_icon(void);
QPixmap * get_m_flash_icon(void);
QPixmap * get_m_other_icon(void);
QPixmap * get_m_floppy_icon(void);
QPixmap * get_v_folderlocked_icon(void);
QPixmap * get_v_folderclosed_icon(void);
QPixmap * get_v_folderopen_icon(void);
QPixmap * get_v_file_icon(void);
QPixmap * get_v_back_icon(void);
QPixmap * get_p_icon(void);
QPixmap * get_t_open_icon(void);
QPixmap * get_t_save_icon(void);
QPixmap * get_t_saveas_icon(void);
QPixmap * get_t_close_icon(void);
QPixmap * get_t_add_icon(void);
QPixmap * get_t_rescan_icon(void);
QPixmap * get_t_delete_icon(void);
QPixmap * get_t_config_icon(void);
QPixmap * get_t_help_icon(void);
QPixmap * get_t_new_icon(void);
QPixmap * get_t_find_icon(void);
QPixmap * get_t_about_icon(void);
QPixmap * get_t_comment_icon(void);
QPixmap * get_anim(int i);
QPixmap * get_t_add_export_icon(void);
QPixmap * get_t_remove_export_icon(void);
QPixmap * get_t_deletec_icon(void);
QPixmap * get_t_showc_icon(void);
QPixmap * get_m_export_icon(void);
QPixmap * get_m_borrow_icon(void);
QPixmap * get_m_import_icon(void);
QPixmap * get_t_sborrow_icon(void);
QPixmap * get_t_cborrow_icon(void);
QPixmap * get_t_colorconfig_icon(void);

#endif



