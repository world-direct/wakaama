#include "LWM2MObjectBase.h"

LWM2MObjectBase::LWM2MObjectBase(uint16_t objID) : _lwm2mObject() {

    this->_lwm2mObject.objID = objID;
    this->_lwm2mObject.readFunc = &LWM2M_Read;
    this->_lwm2mObject.writeFunc = &LWM2M_Write;
    this->_lwm2mObject.executeFunc = &LWM2M_Execute;
    this->_lwm2mObject.discoverFunc = &LWM2M_Discover;
    this->_lwm2mObject.createFunc = &LWM2M_Create;
    this->_lwm2mObject.deleteFunc = &LWM2M_Delete;
    this->_lwm2mObject.userData = this;

}

lwm2m_object_t * LWM2MObjectBase::GetLWM2MObject() {
    return &(this->_lwm2mObject);
}

uint8_t LWM2MObjectBase::LWM2M_Read(uint16_t instanceId, int * numDataP, lwm2m_data_t ** dataArrayP, lwm2m_object_t * objectP) {

	LWM2MObjectBase* _this = (LWM2MObjectBase*)objectP->userData;
	return _this->Read(instanceId, numDataP, dataArrayP, objectP);

}

uint8_t LWM2MObjectBase::LWM2M_Write(uint16_t instanceId, int numData, lwm2m_data_t * dataArrayP, lwm2m_object_t * objectP) {

	LWM2MObjectBase* _this = (LWM2MObjectBase*)objectP->userData;
	return _this->Write(instanceId, numData, dataArrayP, objectP);

}

uint8_t LWM2MObjectBase::LWM2M_Execute(uint16_t instanceId, uint16_t resourceId, uint8_t * buffer, int length, lwm2m_object_t * objectP) {

	LWM2MObjectBase* _this = (LWM2MObjectBase*)objectP->userData;
	return _this->Execute(instanceId, resourceId, buffer, length, objectP);

}

uint8_t LWM2MObjectBase::LWM2M_Discover(uint16_t instanceId, int * numDataP, lwm2m_data_t ** dataArrayP, lwm2m_object_t * objectP) {

	LWM2MObjectBase* _this = (LWM2MObjectBase*)objectP->userData;
	return _this->Discover(instanceId, numDataP, dataArrayP, objectP);

}

uint8_t LWM2MObjectBase::LWM2M_Create(uint16_t instanceId, int numData, lwm2m_data_t * dataArray, lwm2m_object_t * objectP) {

	LWM2MObjectBase* _this = (LWM2MObjectBase*)objectP->userData;
	return _this->Create(instanceId, numData, dataArray, objectP);

}

uint8_t LWM2MObjectBase::LWM2M_Delete(uint16_t instanceId, lwm2m_object_t * objectP) {

	LWM2MObjectBase* _this = (LWM2MObjectBase*)objectP->userData;
	return _this->Delete(instanceId, objectP);

}

uint8_t LWM2MObjectBase::HandleInternalValueChange(lwm2m_data_t * dataArray, lwm2m_object_t * objectP) {
	return COAP_405_METHOD_NOT_ALLOWED;
}

uint8_t LWM2MObjectBase::PerformValueChange(lwm2m_context_t * lwm2mH, lwm2m_uri_t * uri, const char * value, size_t valueLength) {
	
	lwm2m_object_t * refObject = (lwm2m_object_t *)LWM2M_LIST_FIND(lwm2mH->objectList, uri->objectId);
	lwm2m_object_t * object = this->GetLWM2MObject();
	
	if (object != refObject) {
		wd_log_error("LWM2MObjectBase -> Object unknown in the given context");
		return COAP_405_METHOD_NOT_ALLOWED;
	}
	
	if(this->_lwm2mObject.objID != uri->objectId){
		wd_log_error("LWM2MObjectBase -> Uri doesn't address this object");
		return COAP_405_METHOD_NOT_ALLOWED;
	}
	
	lwm2m_data_t * dataP;
	int result;

	dataP = lwm2m_data_new(1);
	dataP->id = uri->resourceId;
	lwm2m_data_encode_nstring(value, valueLength, dataP);

	result = this->Write(uri->instanceId, 1, dataP, object);
	
	if (result == COAP_405_METHOD_NOT_ALLOWED) {
		result = this->HandleInternalValueChange(dataP, object);
	}
	
	lwm2m_data_free(1, dataP);

	if (result != COAP_204_CHANGED) {
		wd_log_error("LWM2MObjectBase -> Failed to change value.");
		return result;
	}
	
	wd_log_info("LWM2MObjectBase -> Value changed");
	lwm2m_resource_value_changed(lwm2mH, uri);
	
	return result;
	
}
