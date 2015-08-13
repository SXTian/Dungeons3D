/*****************************************************************************************
Project      : 3D Game Engine
Author       : Sam Tian
Contributors :
******************************************************************************************/
#pragma once

#include "BaseView.h"
#include <memory>

namespace Dungeons3D
{
  class Camera;

  class CameraView : public BaseView
  {
  public:
    CameraView(std::shared_ptr<Camera> pCamera);
    virtual ~CameraView() {}

    Camera& GetCamera();

    Mtx44 WCMatrix();                 //  get world-camera matrix
    Mtx44 MCMatrix();                 //  get cached model-camera matrix; if no cache, returns world-camera matrix
    Mtx44 MCMatrix(Mtx44 mMatrix);    //  get model-camera matrix with new model transformation (and caching it for future use)

    
  private:
    std::shared_ptr<Camera> m_camera;
    Mtx44 m_mcMatrix;
  };
}