#pragma once

#include "SceneGraph.h"

#include <Frustum.h>

namespace Nome::Scene
{

using tc::Matrix4;
using tc::Frustum;

/*
 * Special scene node that also contains the view info
 */
class CCamera: public CSceneNode
{
public:
    using CSceneNode::CSceneNode;

    void CalculateProjMatrix() const;

    const Matrix4& GetProjMatrix() const;

    Matrix4 GetViewMatrix() const;

    Frustum GetFrustum() const;

    CSceneTreeNode* GetPrincipleTreeNode() const;

    ///Property getter/setter
    float GetAspectRatio() const { return AspectRatio; }
    void SetAspectRatio(float value)
    {
        AspectRatio = value;
        bProjMatrixDirty = true;
    }

    float GetFovY() const { return FovY; }
    void SetFovY(float value)
    {
        FovY = value;
        bProjMatrixDirty = true;
    }

    float GetNearClip() const { return NearClip; }
    void SetNearClip(float value)
    {
        NearClip = value;
        bProjMatrixDirty = true;
    }

    float GetFarClip() const { return FarClip; }
    void SetFarClip(float value)
    {
        FarClip = value;
        bProjMatrixDirty = true;
    }

	void ShowDebugImGui();

private:
    //bool bIsOrthographic = false;
    float AspectRatio = 1.0f;
    ///The vertical field of view, the default is 59 degrees
    float FovY = 59.0f;
    float NearClip = 0.1f;
    float FarClip = 1000.0f;
    //float Zoom;
    //float OrthoSize;

    mutable Matrix4 ProjMatrix;
    mutable bool bProjMatrixDirty = true;
};

}
