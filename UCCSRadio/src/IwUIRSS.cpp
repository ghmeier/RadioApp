/*
 * This file is part of the Marmalade SDK Code Samples.
 *
 * (C) 2001-2012 Marmalade. All Rights Reserved.
 *
 * This source code is intended only as a supplement to the Marmalade SDK.
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 */

//-----------------------------------------------------------------------------
// ExampleIwUIRSS
//-----------------------------------------------------------------------------

/**
 * @page ExampleIwUIRSS IwUI RSS Example
 * The following example fetches RSS feeds from the web and displays them.
 *
 * The main classes used to achieve this are:
 *  - CIwUIView
 *  - CIwUIElement
 *  - CIwUIButton
 *  - CIwUILabel
 *  - CIwUIImage
 *  - CIwHTTP
 *
 * The main functions used to achieve this are:
 *  - IwUIInit()
 *  - IwUITerminate();
 *
 * This example demonstrates fetching RSS feeds using the CIwHTTP class and displaying them
 * dynamically on a UI. The example allows the user to maintain a list of feeds that will be
 * fetched by the IwRSS class and stored persistently in feeds.bin.
 *
 * In the example the news items are parsed and populate a CIwUIScrollableView. If the news
 * item contains an image then it is downloaded and appended to the description.
 *
 * The functions below AddRSSEntry() and AddRSSImage() add content dynamically
 * to the UI. AddRSSEntry clones a template while AddRSSImage creates a new CIwUIImage
 * and sets its texture property to the downloaded image.
 *
 * A SetView() function is used to switch the dialog displayed by the application.
 * It calls SetModal to change which element is intersected with and displays a pop-up
 * animation when switching to the edit or quit dialog.
 *
 * The CIwUIHandleKey class handles OK, Action and Back key presses to perform the
 * correct action.
 *
 * The stylesheet is changed automatically so that the elements are larger on
 * high resolution screens.
 *
 * @image html IwUIRSSImage.png
 *
 * @include IwUIRSS.cpp
 */

// Library includes
#include "IwGx.h"
#include "IwGxFont.h"
#include "IwUI.h"
#include "IwUIAnimation.h"
#include "IwUIController.h"
#include "IwUIButton.h"
#include "IwUICheckbox.h"
#include "IwUIElement.h"
#include "IwUIEvent.h"
#include "IwUILabel.h"
#include "IwUISlider.h"
#include "IwUIView.h"
#include "IwUIProgressBar.h"
#include "IwUIPropertySet.h"
#include "s3eKeyboard.h"
#include "s3eOSExec.h"
#include "s3eOSReadString.h"
#include "IwUISoftKeyboard.h"
#include "IwUITextInput.h"
#include "IwRSS.h"
#include "IwJPEG.h"
#include "IwFeedList.h"
#include "IwModalStack.h"

extern bool g_IwTextureAssertPowerOf2;

// The Base UI Element of the Application
CIwUIElement* g_RSS;
// Pointers to the Edit boxes
CIwUITextField* g_TextTitle, *g_TextURL;
// The feed list and item templates
CIwUIElement* g_Feeds, *g_ItemTemplate, *g_FeedTemplate;
// UI elements
CIwUIElement *g_View, *g_Main, *g_Edit;
// The focus elements
CIwUIElement* g_OldFocus, *g_NewFocus;
// The quit dialog
CIwUIElement* g_QuitScreen;
// The remove button
CIwUIButton* g_Remove;
// The title
CIwUILabel* g_Title;

// Resource group to hold the image textures
CIwResGroup* g_ImageTextures;

// Load the default Stylesheet
static const char* s_Stylesheets[] =
{
    "RSS-Style",            // Original Size
    "RSS-Style-x1.5",       // 1.5x Size
    "RSS-Style-x2.0",       // Double Size
    "RSS-Style-x1.5font",   // Only Font x1.5
};

enum IwUIRSSView
{
    IW_UI_RSS_MAIN,         // The main RSS screen
    IW_UI_RSS_FEED,         // Screen to view RSS feeds
    IW_UI_RSS_ADDEDIT,      // Add/Edit screen
    IW_UI_RSS_QUIT,         // The quit screen
};

//Hold the UI state
int LoadFeed = -1;
int ViewFeed = -1;
int EditFeed = -1;

bool g_Quit;

void ClearList();
void SetView(int mode);

void ClickEditFeed(CIwUIElement * pFocus)
{
    // Find the feed corresponding to the Element with focus
    EditFeed = IwGetFeedList()->ClickEdit(pFocus);

    // Hide the remove button
    g_Remove->SetVisible(true);

    // If the feed is valid, switch to edit view
    if (EditFeed >= 0)
    {
        g_Title->SetCaption("Edit Feed");
        SetView(IW_UI_RSS_ADDEDIT);
    }
}

void ClickAddFeed()
{
    // Update captions
    g_Title->SetCaption("Add New Feed");
    g_TextTitle->SetCaption("New Title");
    g_TextURL->SetCaption("http://");
    g_Remove->SetVisible(false);

    // Switch to the add feed view
    EditFeed = -1;
    SetView(IW_UI_RSS_ADDEDIT);
}


struct CIwUIHandleKey : public CIwUIElementEventHandler
{
    virtual bool FilterEvent(CIwEvent* pEvent)
    {
        if (pEvent->GetID() == IWUI_EVENT_KEY)
        {
            CIwUIEventKey* pEventKey = IwSafeCast<CIwUIEventKey*>(pEvent);
            if (!pEventKey->GetPressed())
            {
                if (pEventKey->GetKey() == s3eKeyAbsOk) // Handle OK button on device
                {
                    if (g_Main->IsVisible())
                    {
                        // Find the correct feed based on the element
                        LoadFeed = IwGetFeedList()->ClickFetch(IwGetUIView()->GetFocus());
                        if (LoadFeed >= 0) return true;
                    }
                }
                else if (pEventKey->GetKey() == s3eKeyAbsBSK) // Handle BSK
                {
                    if (g_Main->IsVisible())
                    {
                        // Edit an existing feed
                        ClickEditFeed(IwGetUIView()->GetFocus());
                        return true;
                    }
                    else if (g_View->IsVisible())
                    {
                        // Clear current list and fetch
                        ClearList();
                        IwGetFeedList()->FetchFeed(0);
                        return true;
                    }
                }
                else if (pEventKey->GetKey() == s3eKeyAbsASK) // Handle ASK
                {
                    if (g_Main->IsVisible())
                    {
                        // Add a new feed
                        ClickAddFeed();
                        return true;
                    }
                    else if (g_View->IsVisible())
                    {
                        // Cancel any active http sessions
                        g_IwRSS->CancelFetch();

                        SetView(IW_UI_RSS_MAIN);
                        return true;
                    }
                }
            }
        }

        // Return false so that the event continues to propogate
        return false;
    }

    virtual void Clone(CIwUIElementEventHandler* pTarget) const
    {
        IW_UI_CLONE_SUPERCLASS(pTarget, CIwUIHandleKey, CIwUIElementEventHandler)
    }
};


// Controller class to handle button clicks
class CController : public CIwUIController
{
public:
    CController()
    {
        IW_UI_CREATE_VIEW_SLOT1(this, "CController", CController, OnClickAdd, CIwUIElement*)
        IW_UI_CREATE_VIEW_SLOT1(this, "CController", CController, OnClickEdit, CIwUIElement*)
        IW_UI_CREATE_VIEW_SLOT1(this, "CController", CController, OnClickBack, CIwUIElement*)
        IW_UI_CREATE_VIEW_SLOT1(this, "CController", CController, OnClickRefresh, CIwUIElement*)
        IW_UI_CREATE_VIEW_SLOT1(this, "CController", CController, OnClickQuit, CIwUIElement*)
        IW_UI_CREATE_VIEW_SLOT1(this, "CController", CController, OnClickFetch, CIwUIElement*)
        IW_UI_CREATE_VIEW_SLOT1(this, "CController", CController, OnClickOK, CIwUIElement*)
        IW_UI_CREATE_VIEW_SLOT1(this, "CController", CController, OnClickCancel, CIwUIElement*)
        IW_UI_CREATE_VIEW_SLOT1(this, "CController", CController, OnClickRemove, CIwUIElement*)
        IW_UI_CREATE_VIEW_SLOT1(this, "CController", CController, OnClickShowQuitScreen, CIwUIElement*)
        IW_UI_CREATE_VIEW_SLOT1(this, "CController", CController, OnClickHideQuitScreen, CIwUIElement*)
    }

private:
    void OnClickAdd(CIwUIElement* Clicked)
    {
        // Add a new feed
        ClickAddFeed();
    }

    void OnClickEdit(CIwUIElement* Clicked)
    {
        // Edit an existing feed
        ClickEditFeed(g_OldFocus);
    }

    void OnClickBack(CIwUIElement* Clicked)
    {
        // Cancel any active http sessions
        g_IwRSS->CancelFetch();

        // Return the main screen
        SetView(IW_UI_RSS_MAIN);
    }

    void OnClickRefresh(CIwUIElement*)
    {
        // Clear current list and fetch
        ClearList();
        IwGetFeedList()->FetchFeed(0);
    }

    void OnClickShowQuitScreen(CIwUIElement*)
    {
        // Open the quit dialog
        SetView(IW_UI_RSS_QUIT);
    }

    void OnClickHideQuitScreen(CIwUIElement*)
    {
        // Hide the quit dialog
        g_QuitScreen->SetVisible(false);
        IwModalStackSetModal(NULL);
    }

    void OnClickQuit(CIwUIElement*)
    {
        // Quit the application
        static bool disableExit =
            s3eDeviceGetInt(S3E_DEVICE_OS) == S3E_OS_ID_WS8 ||
            s3eDeviceGetInt(S3E_DEVICE_OS) == S3E_OS_ID_WS81;

        if (!disableExit)
        {
            s3eDeviceRequestQuit();
        }
    }

    void OnClickFetch(CIwUIElement* pElement)
    {
        // Find the correct feed based on the clicked element
        LoadFeed = IwGetFeedList()->ClickFetch(pElement);
    }

    void OnClickOK(CIwUIElement*)
    {
        // Edit/Add feed and return to main screen
        if (EditFeed >= 0)
            IwGetFeedList()->EditFeed(EditFeed, g_TextTitle->GetCaption(), g_TextURL->GetCaption());
        else
            IwGetFeedList()->AddFeed(g_TextTitle->GetCaption(), g_TextURL->GetCaption());

        SetView(IW_UI_RSS_MAIN);
    }

    void OnClickCancel(CIwUIElement*)
    {
        // Return to main screen
        SetView(IW_UI_RSS_MAIN);
    }

    void OnClickRemove(CIwUIElement*)
    {
        // Remove feed and return to main screen
        if (EditFeed >= 0)
            IwGetFeedList()->RemoveFeed(EditFeed);

        SetView(IW_UI_RSS_MAIN);
    }

};

class CTextInput : public CIwUITextInput
{
public:
    CTextInput()
    {

    }

protected:
    virtual void SetSoftKeyboardModal(CIwUISoftKeyboard* pSoftkeyboard)
    {
        if (pSoftkeyboard)
        {
            // Prevent the UI from rendering the dialog behind the fullscreen keyboard
            if (!pSoftkeyboard->UsingInlineEditor())
            {
                g_RSS->SetVisible(false);
                g_Edit->SetVisible(false);
            }
        }
        else
        {
            g_RSS->SetVisible(true);

            if (IwGetModalStack()->Contains(g_Edit))
                g_Edit->SetVisible(true);
        }

        IwModalStackSetModal(pSoftkeyboard);
    }
};

void ClearList()
{
    // Clear all existing items
    for (int i=g_Feeds->GetNumChildren()-1;i>=0;--i)
    {
        CIwUIElement * child = g_Feeds->GetChild(i);
        g_Feeds->RemoveChild(child);
        delete child;
    }

    // Destroy all previously uploaded images
    IwGetResManager()->DestroyGroup(g_ImageTextures);
    g_ImageTextures = new CIwResGroup;
    IwGetResManager()->AddGroup(g_ImageTextures);
}

// Add News items to the Scrollable View
void AddRSSEntry(const char* title, const char* description)
{
    if (ViewFeed >= 0)
    {
        IwGetUIAnimManager()->StopAnim(g_Feeds);
        g_Feeds->SetProperty("offset", CIwVec2::g_Zero);
        g_Feeds->SetProperty("visible", true);

        ClearList();
        ViewFeed = -1;
    }

    // Instantiate the new item
    CIwUIElement* pItem = g_ItemTemplate->Clone();

    // Set name/value
    IwSafeCast<CIwUILabel*>(pItem->GetChildNamed("Title"))->SetCaption(title);

    // If title and description are the same, don't bother repeating
    if (!strcmp(title, description))
    {
        CIwUIElement* pDescription = pItem->GetChildNamed("Description");
        pDescription->GetParent()->RemoveChild(pDescription);
        delete pDescription;
    }
    else
    {
        IwSafeCast<CIwUILabel*>(pItem->GetChildNamed("Description"))->SetCaption(description);
    }

    // Generate a unique name for the new item
    static int32 itemnum = 0;
    char buf[20];
    sprintf(buf, "item_%d", itemnum++);
    pItem->SetName(buf);

    CIwUILayoutVertical* pLayout = (CIwUILayoutVertical*)g_Feeds->GetLayout();
    pLayout->AddElement(pItem);
}

// Add an image to a news item
void AddRSSImage(const char* title, const char* buf, int len)
{
    // Loop through the news items looking for the correct title
    for (int i=0;i<g_Feeds->GetNumChildren();i++)
    {
        CIwUIElement* feedEntry = g_Feeds->GetChild(i);

        CIwUILabel * label;
        feedEntry->LookupChildNamed(label, "Title", true, true);

        if (label && !strcmp(title, label->GetCaption()))
        {
            // Create a texture from the downloaded image.
            CIwTexture * ImageTex = new CIwTexture();

            // Identify JPEG
            if (IsJPEG(buf, len))
            {
                JPEGTexture(buf, len, *ImageTex);
            }
            else
            {
                CIwImage image;

                s3eFile* pFile = s3eFileOpenFromMemory((void*)buf, len);
                image.ReadFile(pFile);
                s3eFileClose(pFile);

                ImageTex->CopyFromImage(&image);
            }

            ImageTex->Upload();

            // Add the texture to a group so it can be freed later
            g_ImageTextures->AddRes(IW_GX_RESTYPE_TEXTURE, ImageTex);

            CIwUIElement* vertical;
            feedEntry->LookupChildNamed(vertical, "Labels");

            CIwUIImage* pImage = new CIwUIImage;
            pImage->SetName("Image");
            pImage->SetProperty("texture", ImageTex);
            pImage->SetSizeToContent(true);

            vertical->GetLayout()->AddElement(pImage, IW_UI_ALIGN_LEFT, IW_UI_ALIGN_MIDDLE, CIwSVec2(4,4));
            return;
        }
    }
}

void SetView(int mode)
{
    if (mode == IW_UI_RSS_MAIN)
    {
        // Reset feed
        ViewFeed = -1;

        // Set the title
        g_Title->SetCaption("My Feeds");

        // Hide all other screens
        g_QuitScreen->SetVisible(false);
        g_Edit->SetVisible(false);
        g_View->SetVisible(false);

        IwGetUIAnimManager()->StopAnim(g_Feeds);
        g_Feeds->SetProperty("offset", CIwVec2::g_Zero);
        g_Feeds->SetProperty("visible", true);


        // Update the list of feeds
        IwGetFeedList()->Update();
        IwModalStackSetModal(NULL);
        g_Main->SetVisible(true);
    }
    else if (mode == IW_UI_RSS_FEED)
    {
        // Switch to the feed view
        g_Edit->SetVisible(false);
        g_Main->SetVisible(false);
        g_View->SetVisible(true);

        {
            // Play animation
            IwGetUIAnimManager()->StopAnim(g_Feeds);
            IwGetUIAnimManager()->PlayAnim("slideAnim", g_Feeds,
                false, false, -1, -1, IW_GEOM_ONE, g_Feeds->GetSize());
        }

    }
    else if (mode == IW_UI_RSS_ADDEDIT)
    {
        // Display the add/edit dialog
        g_Main->SetVisible(false);
        g_Edit->SetVisible(true);

        IwModalStackSetModal(g_Edit);

        {
            // Play an anim on this element
            IwGetUIAnimManager()->StopAnim(g_Edit);
            IwGetUIAnimManager()->PlayAnim("popupAnim", g_Edit, true);
        }
    }
    else if (mode == IW_UI_RSS_QUIT)
    {
        // Display the quit dialog
        g_QuitScreen->SetVisible(true);

        IwModalStackSetModal(g_QuitScreen);

        {
            // Play an anim on this element
            IwGetUIAnimManager()->StopAnim(g_QuitScreen);
            IwGetUIAnimManager()->PlayAnim("popupAnim", g_QuitScreen, true);
        }
    }
}

#ifdef IW_DEBUG
void DebugSwitchStylesheet(CIwResGroup* pResGroup)
{
    if (IwGetModalStack()->IsEmpty()) // Avoid changing style during text entry
    {
        // Cycle Stylesheets
        if (s3eKeyboardGetState(s3eKeyS))
        {
            CIwResource* pResource = pResGroup->GetResNamed(s_Stylesheets[0], IW_UI_RESTYPE_STYLESHEET);
            IwGetUIStyleManager()->SetStylesheet(IwSafeCast<CIwUIStylesheet*>(pResource));
            IwGetUIView()->Layout();
        }
        else if (s3eKeyboardGetState(s3eKeyM))
        {
            CIwResource* pResource = pResGroup->GetResNamed(s_Stylesheets[1], IW_UI_RESTYPE_STYLESHEET);
            IwGetUIStyleManager()->SetStylesheet(IwSafeCast<CIwUIStylesheet*>(pResource));
            IwGetUIView()->Layout();
        }
        else if (s3eKeyboardGetState(s3eKeyL))
        {
            CIwResource* pResource = pResGroup->GetResNamed(s_Stylesheets[2], IW_UI_RESTYPE_STYLESHEET);
            IwGetUIStyleManager()->SetStylesheet(IwSafeCast<CIwUIStylesheet*>(pResource));
            IwGetUIView()->Layout();
        }
        else if (s3eKeyboardGetState(s3eKeyF))
        {
            CIwResource* pResource = pResGroup->GetResNamed(s_Stylesheets[3], IW_UI_RESTYPE_STYLESHEET);
            IwGetUIStyleManager()->SetStylesheet(IwSafeCast<CIwUIStylesheet*>(pResource));
            IwGetUIView()->Layout();
        }
    }
}
#endif

int main()
{
    g_IwTextureAssertPowerOf2 = false;
    g_Quit = false;

    // Initialize IwUI
    IwUIInit();

    {
        // Instantiate the view and controller singletons.
        CIwUIView view;
        CController controller;
        CIwUIHandleKey key;
        CIwModalStack modalstack;
        CIwFeedList feedlist;

        // Load the resource group
        CIwResGroup* pResGroup = IwGetResManager()->LoadGroup("IwUIRSS.group");

        {
            // Cut-off sizes for stylesheet scale decision
            const int32 area_0 = (320*480); // Smaller/Equal than this uses small style
            const int32 area_1 = (800*480); // Larger/Equal than this uses large style
            const int32 actual_area = s3eSurfaceGetInt(S3E_SURFACE_HEIGHT)
                                     *s3eSurfaceGetInt(S3E_SURFACE_WIDTH);
            int32 style_id = 1;
            if (actual_area<=area_0)
                style_id = 0;
            else
            if (actual_area>=area_1)
                style_id = 2;


            CIwResource* pResource = pResGroup->GetResNamed(s_Stylesheets[style_id], IW_UI_RESTYPE_STYLESHEET);
            IwGetUIStyleManager()->SetStylesheet(IwSafeCast<CIwUIStylesheet*>(pResource));
        }

        // Create the main UI
        g_RSS = CIwUIElement::CreateFromResource("RSS");
        view.AddElement(g_RSS);
        view.AddElementToLayout(g_RSS);

        // Create the edit dialog
        g_Edit = CIwUIElement::CreateFromResource("Edit");
        view.AddElement(g_Edit);
        view.AddElementToLayout(g_Edit);

        // Create the quit dialog
        g_QuitScreen = CIwUIElement::CreateFromResource("Quit");
        view.AddElement(g_QuitScreen);
        view.AddElementToLayout(g_QuitScreen);

        // Find the feed list
        g_Feeds = g_RSS->GetChildNamed("Feeds");

        // Find the item templates
        g_FeedTemplate = (CIwUIElement*)IwGetResManager()->GetResNamed("FeedItemTemplate", "CIwUIElement");
        g_ItemTemplate = (CIwUIElement*)IwGetResManager()->GetResNamed("RSSItemTemplate", "CIwUIElement");

        // Get the progress bar
        CIwUIProgressBar* pProgress = (CIwUIProgressBar*)g_RSS->GetChildNamed("Progress");

        // Find the title
        g_Title = (CIwUILabel*)g_RSS->GetChildNamed("TitleLabel");

        // Find the bottom panel and its contents
        g_View = g_RSS->GetChildNamed("View");
        g_Main = g_RSS->GetChildNamed("Main");

        // Find the elements inside the edit dialog
        g_TextTitle = (CIwUITextField*)g_Edit->GetChildNamed("TextFieldTitle");
        g_TextURL = (CIwUITextField*)g_Edit->GetChildNamed("TextFieldURL");
        g_Remove = (CIwUIButton*)g_Edit->GetChildNamed("Remove");

        // Find the edit button
        CIwUIButton* pEditButton = (CIwUIButton*)g_RSS->GetChildNamed("ButtonEdit");

        // Read Feed List by Serialisation
        if (IwSerialiseExists("feeds.bin"))
        {
            IwSerialiseOpen("feeds.bin", true);
            IwGetFeedList()->Serialise();
            IwSerialiseClose();
        }

        // Instantiate the RSS class and texture group
        g_IwRSS = new CIwRSS();
        g_ImageTextures = new CIwResGroup;

        // Handle key presses
        g_RSS->AddEventHandler(&key);

        // Update the list of feeds
        IwGetFeedList()->Update();

        // Create text input singleton
        CTextInput textinput;
        textinput.CreateSoftKeyboard();

        // Give the quit button focus by default
        CIwUIElement* pFocusElement = g_RSS->GetChildNamed("ButtonQuit");
        IwGetUIView()->RequestFocus(pFocusElement);

        int32 updateTime = 0;
        while (!g_Quit)
        {
            int64 start = s3eTimerGetMs();

            IwGxClear(IW_GX_COLOUR_BUFFER_F | IW_GX_DEPTH_BUFFER_F);

            if (LoadFeed != -1)
            {
                // View the feed
                SetView(IW_UI_RSS_FEED);

                // Begin fetching the feed
                IwGetFeedList()->FetchFeed(LoadFeed);
                ViewFeed = 0;

                LoadFeed = -1;
            }

            // Update the RSS object
            g_IwRSS->Update();

            // Set the value on the progress bar
            pProgress->SetProgress(g_IwRSS->GetProgress());

            // Update the current focus
            g_OldFocus = g_NewFocus;
            g_NewFocus = IwGetUIView()->GetFocus();
            if (g_NewFocus == pEditButton)
                g_NewFocus = g_OldFocus;

            // Enable the edit button
            if (IwGetFeedList()->GetFeed(g_NewFocus) >= 0)
                pEditButton->SetEnabled(true);
            else
                pEditButton->SetEnabled(false);

            IwGetUIController()->Update();

            IwGetUIView()->Update(updateTime);
            IwGetUIView()->Render();

            IwGxFlush();
            IwGxSwapBuffers();
            s3eDeviceYield();
            s3eKeyboardUpdate();
            s3ePointerUpdate();

            // Attempt frame rate
            int32 frameTime = 1000 / 30; // 30fps
            int32 tickTime = (int32)(s3eTimerGetMs() - start);

            if (tickTime < frameTime)
            {
                int32 yield = frameTime - tickTime;
                yield = MAX(0, MIN(yield, 1000));
                s3eDeviceYield(yield);
            }

            updateTime = (int32)(s3eTimerGetMs() - start);
            updateTime = MAX(frameTime, MIN(updateTime, 1000));

            #ifdef IW_DEBUG
            DebugSwitchStylesheet(pResGroup);
            #endif

            g_Quit |= (s3eDeviceCheckQuitRequest() != 0);
        }

        // Save Event Date List by Serialisation
        IwSerialiseOpen("feeds.bin", false);
        IwGetFeedList()->Serialise();
        IwSerialiseClose();

        // Destroy the resource group
        IwGetResManager()->DestroyGroup(pResGroup);
        IwGetResManager()->DestroyGroup(g_ImageTextures);

        // Delete Animation
        IwGetUIAnimManager()->StopAllAnims();

        // Detach event handler
        g_RSS->RemoveEventHandler(&key);

        // Delete the RSS object
        delete g_IwRSS;
    }

    // Terminate the IwUI module
    IwUITerminate();
    return 0;
}
