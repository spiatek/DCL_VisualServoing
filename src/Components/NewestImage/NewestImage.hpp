/*!
 * \file
 * \brief
 */

#ifndef NEWESTIMAGE_PROCESSOR_HPP_
#define NEWESTIMAGE_PROCESSOR_HPP_

#include <opencv2/core/core.hpp>

#include "Component_Aux.hpp"
#include "Component.hpp"
#include "DataStream.hpp"
#include "EventHandler2.hpp"

namespace Processors {
namespace NewestImage {

/*!
 * \class NewestImage_Processor
 * \brief NewestImage processor class.
 */
class NewestImage_Processor: public Base::Component
{
public:
	/*!
	 * Constructor.
	 */
	NewestImage_Processor(const std::string & name = "");

	/*!
	 * Destructor
	 */
	virtual ~NewestImage_Processor();

	void prepareInterface();

protected:

	/*!
	 * Connects source to given device.
	 */
	bool onInit();

	/*!
	 * Disconnect source from device, closes streams, etc.
	 */
	bool onFinish();

	/*!
	 * Retrieves data from device.
	 */
	bool onStep();

	/*!
	 * Start component
	 */
	bool onStart();

	/*!
	 * Stop component
	 */
	bool onStop();

	void onNewImage();

	Base::DataStreamIn <cv::Mat, Base::DataStreamBuffer::Newest, Base::Synchronization::Mutex> in_img;
	Base::EventHandler2 h_onNewImage;

	Base::DataStreamOut<cv::Mat> out_img;
};

}//: namespace NewestImage
}//: namespace Processors


/*
 * Register processor component.
 */
REGISTER_COMPONENT("NewestImage", Processors::NewestImage::NewestImage_Processor)

#endif /* NEWESTIMAGE_PROCESSOR_HPP_ */
