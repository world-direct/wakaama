#include <string.h>
#include "LWM2MObjectBase.h"

LWM2MObjectBase::LWM2MObjectBase(uint16_t objID) {

    this->_lwm2mObject.objID = objID;
    this->_lwm2mObject.readFunc = &LWM2M_Read;
    this->_lwm2mObject.writeFunc = &LWM2M_Write;
    this->_lwm2mObject.executeFunc = &LWM2M_Execute;
    this->_lwm2mObject.discoverFunc = &LWM2M_Discover;
    this->_lwm2mObject.createFunc = &LWM2M_Create;
    this->_lwm2mObject.deleteFunc = &LWM2M_Delete;
    this->_lwm2mObject.userData = this;
    this->_lwm2mObject.instanceList = (lwm2m_list_t *)lwm2m_malloc(sizeof(lwm2m_list_t));
    if (this->_lwm2mObject.instanceList != NULL){
        memset(this->_lwm2mObject.instanceList, 0, sizeof(lwm2m_list_t));
    }

}

lwm2m_object_t * LWM2MObjectBase::GetLWM2MObject() {
    return &(this->_lwm2mObject);
}

uint8_t LWM2MObjectBase::LWM2M_Read(uint16_t instanceId, int * numDataP, lwm2m_data_t ** dataArrayP, lwm2m_object_t * objectP) {

	LWM2MObjectBase* _this = (LWM2MObjectBase*)objectP->userData;
    return _this->Read(instanceId, numDataP, dataArrayP);

}

uint8_t LWM2MObjectBase::LWM2M_Write(uint16_t instanceId, int numData, lwm2m_data_t * dataArrayP, lwm2m_object_t * objectP) {

	LWM2MObjectBase* _this = (LWM2MObjectBase*)objectP->userData;
	return _this->Write(instanceId, numData, dataArrayP);

}

uint8_t LWM2MObjectBase::LWM2M_Execute(uint16_t instanceId, uint16_t resourceId, uint8_t * buffer, int length, lwm2m_object_t * objectP) {

	LWM2MObjectBase* _this = (LWM2MObjectBase*)objectP->userData;
	return _this->Execute(instanceId, resourceId, buffer, length);

}

uint8_t LWM2MObjectBase::LWM2M_Discover(uint16_t instanceId, int * numDataP, lwm2m_data_t ** dataArrayP, lwm2m_object_t * objectP) {

	LWM2MObjectBase* _this = (LWM2MObjectBase*)objectP->userData;
	return _this->Discover(instanceId, numDataP, dataArrayP);

}

uint8_t LWM2MObjectBase::LWM2M_Create(uint16_t instanceId, int numData, lwm2m_data_t * dataArray, lwm2m_object_t * objectP) {

	LWM2MObjectBase* _this = (LWM2MObjectBase*)objectP->userData;
	return _this->Create(instanceId, numData, dataArray);

}

uint8_t LWM2MObjectBase::LWM2M_Delete(uint16_t instanceId, lwm2m_object_t * objectP) {

	LWM2MObjectBase* _this = (LWM2MObjectBase*)objectP->userData;
	return _this->Delete(instanceId);

}
