/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/
#pragma once

#include "CameraView.h"
#include "Camera.h"

namespace Dungeons3D
{
  CameraView::CameraView(std::shared_ptr<Camera> pCamera) : m_camera(pCamera), m_mcMatrix(pCamera->CamMatrix())
  {
  }

  Camera& CameraView::GetCamera()
  {
    return *m_camera;
  }

  Mtx44 CameraView::WCMatrix()
  {
    return m_camera->CamMatrix();
  }

  Mtx44 CameraView::MCMatrix()
  {
    return m_mcMatrix;
  }

  Mtx44 CameraView::MCMatrix(Mtx44 mMatrix)
  {
    m_mcMatrix = m_camera->CamMatrix().Mult(mMatrix);
    return m_mcMatrix;
  }
}