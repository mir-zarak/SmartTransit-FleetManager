#pragma once
#include <exception>
#include <fstream>
#include <memory>
#include "utilities/CustomString.h"
#include "utilities/CustomDate.h"

class TransitException : public std::exception {
protected:
    CustomString m_message;
    CustomString m_source;
    CustomDate m_timestamp;
    int m_code;

public:
    TransitException(const CustomString& msg = CustomString("Transit error"),
                     const CustomString& src = CustomString("SmartTransit"),
                     int code = 0);
    const char* what() const noexcept override;
    virtual CustomString getCategory() const = 0;
    CustomString getMessage() const;
    int getCode() const;
};

#define TRANSIT_EXCEPTION(NAME, BASE, CAT) \
class NAME : public BASE { \
public: \
    using BASE::BASE; \
    CustomString getCategory() const override { return CustomString(CAT); } \
};

TRANSIT_EXCEPTION(VehicleException, TransitException, "VehicleException")
TRANSIT_EXCEPTION(RouteException, TransitException, "RouteException")
TRANSIT_EXCEPTION(TripException, TransitException, "TripException")
TRANSIT_EXCEPTION(PaymentException, TransitException, "PaymentException")
TRANSIT_EXCEPTION(StaffException, TransitException, "StaffException")
TRANSIT_EXCEPTION(TicketException, TransitException, "TicketException")
TRANSIT_EXCEPTION(FileException, TransitException, "FileException")
TRANSIT_EXCEPTION(ValidationException, TransitException, "ValidationException")
TRANSIT_EXCEPTION(ContainerException, TransitException, "ContainerException")

TRANSIT_EXCEPTION(VehicleNotFoundException, VehicleException, "VehicleNotFoundException")
TRANSIT_EXCEPTION(VehicleOverCapacityException, VehicleException, "VehicleOverCapacityException")
TRANSIT_EXCEPTION(VehicleBreakdownException, VehicleException, "VehicleBreakdownException")
TRANSIT_EXCEPTION(CargoCriticalException, VehicleException, "CargoCriticalException")
TRANSIT_EXCEPTION(RouteNotFoundException, RouteException, "RouteNotFoundException")
TRANSIT_EXCEPTION(StopNotFoundException, RouteException, "StopNotFoundException")
TRANSIT_EXCEPTION(RouteConflictException, RouteException, "RouteConflictException")
TRANSIT_EXCEPTION(TripAlreadyActiveException, TripException, "TripAlreadyActiveException")
TRANSIT_EXCEPTION(TripCancelledException, TripException, "TripCancelledException")
TRANSIT_EXCEPTION(NoDriverAssignedException, TripException, "NoDriverAssignedException")
TRANSIT_EXCEPTION(PaymentDeclinedException, PaymentException, "PaymentDeclinedException")
TRANSIT_EXCEPTION(InsufficientFundsException, PaymentException, "InsufficientFundsException")
TRANSIT_EXCEPTION(InvalidCardException, PaymentException, "InvalidCardException")
TRANSIT_EXCEPTION(DriverNotFoundException, StaffException, "DriverNotFoundException")
TRANSIT_EXCEPTION(LicenseExpiredException, StaffException, "LicenseExpiredException")
TRANSIT_EXCEPTION(UnauthorisedAccessException, StaffException, "UnauthorisedAccessException")
TRANSIT_EXCEPTION(InvalidTicketException, TicketException, "InvalidTicketException")
TRANSIT_EXCEPTION(TicketAlreadyUsedException, TicketException, "TicketAlreadyUsedException")
TRANSIT_EXCEPTION(FileNotFoundException, FileException, "FileNotFoundException")
TRANSIT_EXCEPTION(FileCorruptionException, FileException, "FileCorruptionException")
TRANSIT_EXCEPTION(InvalidDateException, ValidationException, "InvalidDateException")
TRANSIT_EXCEPTION(InvalidTimeException, ValidationException, "InvalidTimeException")
TRANSIT_EXCEPTION(InvalidCoordinateException, ValidationException, "InvalidCoordinateException")
TRANSIT_EXCEPTION(EmptyStringException, ValidationException, "EmptyStringException")
TRANSIT_EXCEPTION(IndexOutOfBoundsException, ContainerException, "IndexOutOfBoundsException")
TRANSIT_EXCEPTION(NullNodeException, ContainerException, "NullNodeException")
TRANSIT_EXCEPTION(GraphVertexNotFoundException, ContainerException, "GraphVertexNotFoundException")
