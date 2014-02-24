/*!
 * \file
 * \brief
 */

#include <memory>
#include <string>

#include "VisualServoIB_Processor.hpp"
#include "Common/Logger.hpp"
#include <boost/bind.hpp>

namespace Processors {
namespace VisualServoIB {

using Types::ImagePosition;
using Types::Mrrocpp_Proxy::IBReading;

VisualServoIB_Processor::VisualServoIB_Processor(const std::string & name) :
	Base::Component(name)
{
	LOG(LTRACE) << "Hello VisualServoIB_Processor\n";
}

VisualServoIB_Processor::~VisualServoIB_Processor()
{
	LOG(LTRACE) << "Good bye VisualServoIB_Processor\n";
}

void VisualServoIB_Processor::prepareInterface()
{
	LOG(LTRACE) << "VisualServoIB_Processor::prepareInterface\n";

	// Register data streams, events and event handlers HERE!
	registerStream("in_position", &in_position);
	registerStream("in_objectNotFound", &in_objectNotFound);
	registerStream("out_reading", &out_reading);

	h_onObjectLocated.setup(boost::bind(&VisualServoIB_Processor::onObjectLocated, this));
	registerHandler("onObjectLocated", &h_onObjectLocated);
	addDependency("onObjectLocated", &in_position);

	h_onObjectNotFound.setup(boost::bind(&VisualServoIB_Processor::onObjectNotFound, this));
	registerHandler("onObjectNotFound", &h_onObjectNotFound);
	addDependency("onObjectNotFound", &in_objectNotFound);

	//readingReady = registerEvent("readingReady");
}

bool VisualServoIB_Processor::onInit()
{
	LOG(LTRACE) << "VisualServoIB_Processor::initialize\n";

	return true;
}

bool VisualServoIB_Processor::onFinish()
{
	LOG(LTRACE) << "VisualServoIB_Processor::finish\n";

	return true;
}

bool VisualServoIB_Processor::onStep()
{
	LOG(LTRACE) << "VisualServoIB_Processor::step\n";
	return true;
}

bool VisualServoIB_Processor::onStop()
{
	return true;
}

bool VisualServoIB_Processor::onStart()
{
	return true;
}

void VisualServoIB_Processor::onObjectLocated()
{
	try{
		LOG(LTRACE) << "VisualServoIB_Processor::onObjectLocated()\n";
		IBReading ibr;
		ibr.objectVisible = true;
		ibr.imagePosition = in_position.read();

		LOG(LDEBUG)<<"ibr.imagePosition = "<<ibr.imagePosition;


		out_reading.write(ibr);
		//readingReady->raise();
	}catch(exception& ex){
		LOG(LERROR) << "VisualServoIB_Processor::onObjectLocated(): " << ex.what();
	}
}

void VisualServoIB_Processor::onObjectNotFound()
{
	LOG(LTRACE) << "VisualServoIB_Processor::onObjectNotFound()\n";
	bool objectNotFound = in_objectNotFound.read();
	if(!objectNotFound) {
		return;
	}
	IBReading ibr;
	ibr.objectVisible = false;
	for (int i = 0; i < ImagePosition::elementsSize; ++i) {
		ibr.imagePosition.elements[i]= 0;
	}
	out_reading.write(ibr);

	//readingReady->raise();
}

}//: namespace VisualServoIB
}//: namespace Processors
