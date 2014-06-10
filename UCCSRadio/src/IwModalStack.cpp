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

// Includes
#include "IwModalStack.h"
#include "IwUIView.h"

// Macros
IW_SINGLETON_INSTANTIATE(ModalStack);
IW_MANAGED_IMPLEMENT_FACTORY(CIwModalStack);

//-----------------------------------------------------------------------------

CIwModalStack::CIwModalStack()
{
    IW_SINGLETON_SET(ModalStack);
}

CIwModalStack::~CIwModalStack()
{
    IW_SINGLETON_CLEAR(ModalStack);
}

CIwUIElement* CIwModalStack::Top() const
{
    if (m_Ptrs.size()>0)
        return m_Ptrs.back();
    else
        return NULL;
}

void CIwModalStack::Push(CIwUIElement* element)
{
    m_Ptrs.push_back(CIwUIElementPtr(element));
}

void CIwModalStack::Pop()
{
    if (m_Ptrs.size()>0)
        m_Ptrs.pop_back();
}

bool CIwModalStack::Contains(CIwUIElement* element) const
{
    for (int i=0; i<(int)m_Ptrs.size(); i++)
    {
        if (m_Ptrs[i] == element)
            return true;
    }
    return false;
}

bool CIwModalStack::IsEmpty() const
{
    return m_Ptrs.empty();
}

void IwModalStackSetModal(CIwUIElement* element)
{
    CIwModalStack* stack = IwGetModalStack();
    // Set
    if (element)
    {
        stack->Push(element);
    }
    else
    {
        stack->Pop();
    }

    IwGetUIView()->SetModal(stack->Top());
}
