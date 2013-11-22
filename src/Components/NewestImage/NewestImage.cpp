/*!
 * \file
 * \brief
 */

#include <memory>
#include <string>
#include <boost/bind.hpp>

#include "NewestImage.hpp"
#include "Common/Logger.hpp"

namespace Processors {
namespace NewestImage {

NewestImage_Processor::NewestImage_Processor(const std::string & name) :
	Base::Component(name)
{
	LOG(LTRACE) << "Hello NewestImage_Processor\n";
}

NewestImage_Processor::~NewestImage_Processor()
{
	LOG(LTRACE) << "Good bye NewestImage_Processor\n";
}

void NewestImage_Processor::prepareInterface()
{
	LOG(LTRACE) << "NewestImage_Processor::initialize\n";

	// Register data streams, events and event handlers HERE!
	registerStream("in_img", &in_img);
	registerStream("out_img", &out_img);

	h_onNewImage.setup(boost::bind(&NewestImage_Processor::onNewImage, this));
	registerHandler("onNewImage", &h_onNewImage);
	addDependency("onNewImage", &in_img);

	//newImage = registerEvent("newImage");
}

bool NewestImage_Processor::onInit()
{
	LOG(LTRACE) << "NewestImage_Processor::initialize\n";

	return true;
}

bool NewestImage_Processor::onFinish()
{
	LOG(LTRACE) << "NewestImage_Processor::finish\n";

	return true;
}

bool NewestImage_Processor::onStep()
{
	LOG(LTRACE) << "NewestImage_Processor::step\n";
	return true;
}

bool NewestImage_Processor::onStop()
{
	return true;
}

bool NewestImage_Processor::onStart()
{
	return true;
}

void NewestImage_Processor::onNewImage()
{
	if(in_img.empty()){
		return;
	}
	out_img.write(in_img.read().clone());
	//newImage->raise();
}

}//: namespace NewestImage
}//: namespace Processors
