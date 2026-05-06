#pragma once
#include "utilities/CustomString.h"
#include "datastructs/LinkedList.h"
class INotifiable {
public:
    virtual ~INotifiable() = default;
    virtual void sendNotification(const CustomString& msg, int priority) = 0;
    virtual LinkedList<CustomString> getDeliveryLog() const = 0;
    virtual void clearLog() = 0;
};
class SMSNotifier : public INotifiable {
    LinkedList<CustomString> log;
public: void sendNotification(const CustomString& msg,int) override { log.push_back(msg); } LinkedList<CustomString> getDeliveryLog() const override { return log; } void clearLog() override { log.clear(); } };
class EmailNotifier : public INotifiable {
    LinkedList<CustomString> log;
public: void sendNotification(const CustomString& msg,int) override { log.push_back(msg); } LinkedList<CustomString> getDeliveryLog() const override { return log; } void clearLog() override { log.clear(); } };
class PushNotifier : public INotifiable {
    LinkedList<CustomString> log;
public: void sendNotification(const CustomString& msg,int) override { log.push_back(msg); } LinkedList<CustomString> getDeliveryLog() const override { return log; } void clearLog() override { log.clear(); } };
class DisplayBoardNotifier : public INotifiable {
    LinkedList<CustomString> log;
public: void sendNotification(const CustomString& msg,int) override { log.push_back(msg); } LinkedList<CustomString> getDeliveryLog() const override { return log; } void clearLog() override { log.clear(); } };
