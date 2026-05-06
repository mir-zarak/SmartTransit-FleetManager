#pragma once
#include "utilities/CustomString.h"
class IPaymentProcessor {
public:
    virtual ~IPaymentProcessor() = default;
    virtual bool processPayment(double amount) = 0;
    virtual bool refund(const CustomString& transactionId) = 0;
    virtual CustomString getPaymentMethod() const = 0;
    virtual CustomString generateTransactionId() const = 0;
    virtual bool validateDetails() const = 0;
};
class CashProcessor : public IPaymentProcessor {
public: bool processPayment(double) override { return true; } bool refund(const CustomString&) override { return true; } CustomString getPaymentMethod() const override { return CustomString("Cash"); } CustomString generateTransactionId() const override { return CustomString("CASH-TX"); } bool validateDetails() const override { return true; } };
class TransitCardProcessor : public IPaymentProcessor {
public: bool processPayment(double) override { return true; } bool refund(const CustomString&) override { return true; } CustomString getPaymentMethod() const override { return CustomString("TransitCard"); } CustomString generateTransactionId() const override { return CustomString("CARD-TX"); } bool validateDetails() const override { return true; } };
class QRCodeProcessor : public IPaymentProcessor {
public: bool processPayment(double) override { return true; } bool refund(const CustomString&) override { return true; } CustomString getPaymentMethod() const override { return CustomString("QRCode"); } CustomString generateTransactionId() const override { return CustomString("QR-TX"); } bool validateDetails() const override { return true; } };
class CorporateAccountProcessor : public IPaymentProcessor {
public: bool processPayment(double) override { return true; } bool refund(const CustomString&) override { return true; } CustomString getPaymentMethod() const override { return CustomString("CorporateAccount"); } CustomString generateTransactionId() const override { return CustomString("CORP-TX"); } bool validateDetails() const override { return true; } };
class LoyaltyPointsProcessor : public IPaymentProcessor {
public: bool processPayment(double) override { return true; } bool refund(const CustomString&) override { return true; } CustomString getPaymentMethod() const override { return CustomString("LoyaltyPoints"); } CustomString generateTransactionId() const override { return CustomString("LOYAL-TX"); } bool validateDetails() const override { return true; } };
