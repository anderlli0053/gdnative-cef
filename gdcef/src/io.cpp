//*************************************************************************
// Stigmee: The art to sanctuarize knowledge exchanges.
// Copyright 2021-2022 Alain Duron <duron.alain@gmail.com>
// Copyright 2021-2022 Quentin Quadrat <lecrapouille@gmail.com>
//
// This file is part of Stigmee.
//
// Stigmee is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//*************************************************************************

#include "gdcef.h"
#include <GlobalConstants.hpp> // Godot

//------------------------------------------------------------------------------
void GDCef::leftClick()
{
    leftMouseDown();
    leftMouseUp();
}

//------------------------------------------------------------------------------
void GDCef::rightClick()
{
    rightMouseDown();
    rightMouseUp();
}

//------------------------------------------------------------------------------
void GDCef::middleClick()
{
    middleMouseDown();
    middleMouseUp();
}

//------------------------------------------------------------------------------
void GDCef::leftMouseDown()
{
    if (!m_browser)
        return;

    CefBrowserHost::MouseButtonType btn = CefBrowserHost::MouseButtonType::MBT_LEFT;
    std::cout << "[GDCEF] [GDCef::leftMouseDown] mouse event occured" << std::endl;
    CefMouseEvent evt;
    std::cout << "[GDCEF] [GDCef::leftMouseDown] x,y" << m_mouse_x << "," << m_mouse_y << std::endl;
    evt.x = m_mouse_x;
    evt.y = m_mouse_y;

    m_browser->GetHost()->SendMouseClickEvent(evt, btn, false, 1);
}

//------------------------------------------------------------------------------
void GDCef::rightMouseDown()
{
    if (!m_browser)
        return;

    CefBrowserHost::MouseButtonType btn = CefBrowserHost::MouseButtonType::MBT_RIGHT;
    std::cout << "[GDCEF] [GDCef::rightMouseDown] mouse event occured" << std::endl;
    CefMouseEvent evt;
    std::cout << "[GDCEF] [GDCef::rightMouseDown] x,y" << m_mouse_x << "," << m_mouse_y << std::endl;
    evt.x = m_mouse_x;
    evt.y = m_mouse_y;

    m_browser->GetHost()->SendMouseClickEvent(evt, btn, false, 1);
}

//------------------------------------------------------------------------------
void GDCef::leftMouseUp()
{
    if (!m_browser)
        return;

    CefBrowserHost::MouseButtonType btn = CefBrowserHost::MouseButtonType::MBT_LEFT;
    std::cout << "[GDCEF] [GDCef::leftMouseUp] mouse event occured" << std::endl;
    CefMouseEvent evt;
    std::cout << "[GDCEF] [GDCef::leftMouseUp] x,y" << m_mouse_x << "," << m_mouse_y << std::endl;
    evt.x = m_mouse_x;
    evt.y = m_mouse_y;

    m_browser->GetHost()->SendMouseClickEvent(evt, btn, true, 1);
}

//------------------------------------------------------------------------------
void GDCef::rightMouseUp()
{
    if (!m_browser)
        return;

    CefBrowserHost::MouseButtonType btn = CefBrowserHost::MouseButtonType::MBT_RIGHT;
    std::cout << "[GDCEF] [GDCef::rightMouseUp] mouse event occured" << std::endl;
    CefMouseEvent evt;
    std::cout << "[GDCEF] [GDCef::rightMouseUp] x,y" << m_mouse_x << "," << m_mouse_y << std::endl;
    evt.x = m_mouse_x;
    evt.y = m_mouse_y;

    m_browser->GetHost()->SendMouseClickEvent(evt, btn, true, 1);
}

//------------------------------------------------------------------------------
void GDCef::middleMouseDown()
{
    if (!m_browser)
        return;

    CefBrowserHost::MouseButtonType btn = CefBrowserHost::MouseButtonType::MBT_MIDDLE;
    std::cout << "[GDCEF] [GDCef::middleMouseDown] mouse event occured" << std::endl;
    CefMouseEvent evt;
    std::cout << "[GDCEF] [GDCef::middleMouseDown] x,y" << m_mouse_x << "," << m_mouse_y << std::endl;
    evt.x = m_mouse_x;
    evt.y = m_mouse_y;

    m_browser->GetHost()->SendMouseClickEvent(evt, btn, false, 1);
}

//------------------------------------------------------------------------------
void GDCef::middleMouseUp()
{
    if (!m_browser)
        return;

    CefBrowserHost::MouseButtonType btn = CefBrowserHost::MouseButtonType::MBT_MIDDLE;
    std::cout << "[GDCEF] [GDCef::middleMouseUp] mouse event occured" << std::endl;
    CefMouseEvent evt;
    std::cout << "[GDCEF] [GDCef::middleMouseUp] x,y" << m_mouse_x << "," << m_mouse_y << std::endl;
    evt.x = m_mouse_x;
    evt.y = m_mouse_y;

    m_browser->GetHost()->SendMouseClickEvent(evt, btn, true, 1);
}

//------------------------------------------------------------------------------
void GDCef::mouseMove(int x, int y)
{
    if (!m_browser)
        return ;

    m_mouse_x = x;
    m_mouse_y = y;

    CefMouseEvent evt;
    evt.x = x;
    evt.y = y;

    bool mouse_leave = false; // TODO
    // AD - Adding focus just like what's done in BLUI
    auto host = m_browser->GetHost();
    host->SetFocus(true);
    host->SendMouseMoveEvent(evt, mouse_leave);
}

//------------------------------------------------------------------------------
void GDCef::mouseWheel(const int wDelta)
{
    if (m_browser == nullptr)
        return ;

    std::cout << "[GDCEF] [GDCef::mouseWheel] mouse wheel rolled" << std::endl;
    CefMouseEvent evt;
    std::cout << "[GDCEF] [GDCef::mouseWheel] x,y,wDelta : [" << m_mouse_x << ","
              << m_mouse_y << "," << wDelta << "]" << std::endl;

    evt.x = m_mouse_x;
    evt.y = m_mouse_y;

    m_browser->GetHost()->SendMouseWheelEvent(evt, wDelta * 10, wDelta * 10);
}

//------------------------------------------------------------------------------
static int getKeyboardModifiers(bool shift, bool alt, bool ctrl)
{
    int modifiers = 0;

    if (shift == true)
        modifiers |= EVENTFLAG_SHIFT_DOWN;
    if (ctrl == true)
        modifiers |= EVENTFLAG_CONTROL_DOWN;
    if (alt == true)
        modifiers |= EVENTFLAG_ALT_DOWN;

    return modifiers;
}

//------------------------------------------------------------------------------
void GDCef::keyPress(int key, bool pressed, bool shift, bool alt, bool ctrl)
{
    if (!m_browser)
        return;

    CefKeyEvent event;
    if (pressed == true)
    {
        // set the event modifier if they are activated
        event.modifiers = getKeyboardModifiers(shift, alt, ctrl);

        if ((key >= 65 && key <= 90)) // CHAR SMALL
        {
            event.windows_key_code = key;
            event.type = KEYEVENT_RAWKEYDOWN;
            m_browser->GetHost()->SendKeyEvent(event);
            event.type = KEYEVENT_CHAR;
            m_browser->GetHost()->SendKeyEvent(event);

        }
        else if (key == 46) // PERIOD
        {
            event.windows_key_code = 46;
            event.character = 46;
            event.unmodified_character = 46;
            event.type = KEYEVENT_CHAR;
            m_browser->GetHost()->SendKeyEvent(event);
        }
        else if (key == godot::GlobalConstants::KEY_SPACE ||
                 key == godot::GlobalConstants::KEY_TAB)
        {
            event.windows_key_code = key;
            event.type = KEYEVENT_RAWKEYDOWN;
            m_browser->GetHost()->SendKeyEvent(event);
            event.type = KEYEVENT_CHAR;
            m_browser->GetHost()->SendKeyEvent(event);
        }
        else if (key == godot::GlobalConstants::KEY_BACKSPACE ||
                 key == godot::GlobalConstants::KEY_ENTER ||
                 key == godot::GlobalConstants::KEY_KP_ENTER ||
                 key == godot::GlobalConstants::KEY_DELETE)
        {
            // TODO : FIXME, Not working yet, duno why
            if (key == godot::GlobalConstants::KEY_BACKSPACE) {
                event.windows_key_code = 8;
                event.character = 8;
                event.unmodified_character = 8;
            }
            else if (key == godot::GlobalConstants::KEY_ENTER) {
                event.windows_key_code = 13;
                event.character = 13;
                event.unmodified_character = 13;
            }
            else if (key == godot::GlobalConstants::KEY_KP_ENTER) {
                event.windows_key_code = 13;
                event.character = 13;
                event.unmodified_character = 13;
            }
            else {
                event.windows_key_code = 127;
                event.character = 127;
                event.unmodified_character = 127;
            }

            //event.native_key_code = key ;
            event.type = KEYEVENT_KEYDOWN;
            m_browser->GetHost()->SendKeyEvent(event);
            event.type = KEYEVENT_CHAR;
            m_browser->GetHost()->SendKeyEvent(event);
        }
        else if ((key >= 48 && key <= 57) ||
                 (key <= 320 && key <= 329)) // NUMBERS & NUMPAD
        {
            event.windows_key_code = key;

            event.type = KEYEVENT_KEYDOWN;
            m_browser->GetHost()->SendKeyEvent(event);
            event.type = KEYEVENT_CHAR;
            m_browser->GetHost()->SendKeyEvent(event);

        }

    }
    else if (pressed == false)
    {
        std::cout << "[GDCEF] [GDCef::KeyPressed] PRESSED FALSE" << std::endl;
        event.native_key_code |= 0xC0000000;
        event.type = KEYEVENT_KEYUP;
        m_browser->GetHost()->SendKeyEvent(event);
    }
}