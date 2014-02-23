/*!
 * \file
 * \brief
 */

#ifndef VISUALSERVOPB_PROCESSOR_PROCESSOR_HPP_
#define VISUALSERVOPB_PROCESSOR_PROCESSOR_HPP_

#include <ctime>

#include "Component_Aux.hpp"
#include "Component.hpp"
#include "DataStream.hpp"
#include "EventHandler2.hpp"
#include "Types/Mrrocpp_Proxy/PBReading.hpp"

/*!
 * \defgroup VisualServoPB_Processor VisualServoPB_Processor
 * \ingroup Processors
 *
 * A component for position-based visual servoing.
 * Receives object's position with respect to the camera or information that object has not been found.
 * Given this information creates reading which will be sent to robot control system.
 *
 * \par Data streams:
 *
 * \streamin{in_position,Types::HomogMatrix}
 * Position of object with respect to camera.
 *
 * \streamout{out_reading,Types::Mrrocpp_Proxy::PBReading}
 * Reading to send to robot control system.
 *
 * \par Events:
 *
 * \event{readingReady}
 * Raised when new reading is ready.
 *
 * \par Event handlers:
 *
 * \handler{onObjectLocated}
 * If object has been located, raise this event.
 * Event handler will read from in_position data stream.
 * New reading will be written to out_reading and readingReady event will be raised.
 *
 * \handler{onObjectNotFound}
 * If object has not been located, raise this event.
 * Event handler will not be read from in_position data stream.
 * New reading will be written to out_reading and readingReady event will be raised.
 *
 * @{
 *
 * @}
 */

namespace Processors {
namespace VisualServoPB {

/*!
 * \class VisualServoPB_Processor
 * \brief VisualServoPB processor class.
 */
class VisualServoPB_Processor: public Base::Component
{
public:
	/*!
	 * Constructor.
	 */
	VisualServoPB_Processor(const std::string & name = "");

	/*!
	 * Destructor
	 */
	virtual ~VisualServoPB_Processor();

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

private:
	void onObjectLocated();
	void onObjectNotFound();

	void saveTime(Types::Mrrocpp_Proxy::PBReading& reading);

	Base::DataStreamIn<Types::HomogMatrix> in_position;
	Base::DataStreamIn<struct timespec> in_timestamp;
	Base::DataStreamOut<Types::Mrrocpp_Proxy::PBReading> out_reading;

	Base::EventHandler2 h_onObjectLocated;
	Base::EventHandler2 h_onObjectNotFound;
};

}//: namespace VisualServoPB
}//: namespace Processors


/*
 * Register processor component.
 */
REGISTER_COMPONENT("VisualServoPB", Processors::VisualServoPB::VisualServoPB_Processor)

#endif /* VISUALSERVOPB_PROCESSOR_PROCESSOR_HPP_ */
