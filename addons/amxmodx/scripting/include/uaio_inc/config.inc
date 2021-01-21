////////////////////////////////////////////////////////////////////////////////////////////
//   config.inc                    Version 1.51                       Date: AUG/01/2006
//
//   RS UAIO (Ultimate All-In-One) Admin Menu System (Multilingual)
//   File: UAIO Admin - Main Source File
//
//   Created By:    Rob Secord, B.Sc.
//   Alias: xeroblood (aka; Achilles; sufferer)
//   Email: xeroblood@msn.com
//
//   Updated By:    Dan Weeks
//   Alias: $uicid3
//   Email: suicid3m3@gmail.com
//
//   This File is part of UAIO (Ultimate All-In-One) Admin Menu.
//
////////////////////////////////////////////////////////////////////////////////////////////

#if defined _UAIO_CONFIG_INCLUDED
  #endinput
#endif
#define _UAIO_CONFIG_INCLUDED

// Compile Configurations:
// To Disable a mode/value, simply add // to the beginning of the #define line.
// To Enable it, remove // from the beginning of the line if it exists

// Uncomment if you get Loose Indentation Warnings on Compile..
//#pragma tabsize 0

// Uncomment for UAIO-DEBUG messages
//#define UAIO_DEBUG_MODE
//#define UAIO_DEBUG_MENU


// Do Not Comment Following Lines, Simply Change Value if needed...
//
// Change to your Desired Super-Admin Access Level (Default ADMIN_LEVEL_A [flag 'm'])
// Admins with this Flag can Turn Entire Plugin On/Off and use Debug mode commands
#define UAIO_LVL_SUPER ADMIN_LEVEL_A

// Change to your Desired Regular-Admin Access Level (Default ADMIN_LEVEL_B [flag 'n'])
// Admins with this Flag can use UAIO Admin Commands that are set in their Admin-Group
// For more info, view 'configs/uaio/uaio_groups.ini' & 'configs/uaio/uaio_admins.ini'
#define UAIO_LVL_ADMIN ADMIN_LEVEL_B

// NOTE:
// --- Super-Admins should have both flags set in configs/users.ini
// --- Other Admins that you want to access this plugin should only have the one flag
//      matching UAIO_LVL_ADMIN (Default flag 'n', unless changed from above)
//

// Following is used to Allow All Players Access to Commands specified by Default Group.
// configs/uaio/uaio_groups.ini MUST have a 'default' group where flags are set for Public
// commands, simply change flags there to disallow Public Players to use specific Commands.
// Public users (under group 'default') will have access to uaio_menu and uaio_help.
// Changing this value is not recommended..
#define UAIO_LVL_USER 0

