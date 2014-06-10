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

#ifndef IW_MODAL_STACK_H
#define IW_MODAL_STACK_H

// Library includes
#include "IwUIElement.h"
#include "IwUIElementPtr.h"

class CIwModalStack
{
public:
    IW_MANAGED_DECLARE(CIwModalStack);
    CIwModalStack();
    virtual ~CIwModalStack();

    CIwUIElement*   Top() const;
    void            Push(CIwUIElement* element);
    void            Pop();

    bool Contains(CIwUIElement* element) const;

    bool IsEmpty() const;

private:
    CIwUIElementPtr::Array m_Ptrs;
};

// Singleton
IW_SINGLETON_EXTERN(ModalStack);

// Function Suitable for Modal Behaviour override
void IwModalStackSetModal(CIwUIElement* element);

#endif
