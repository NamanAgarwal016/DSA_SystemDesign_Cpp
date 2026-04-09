#ifndef ORDER_ENUMS_H
#define ORDER_ENUMS_H

enum class OrderTimeType {
    NOW,
    SCHEDULE
};

enum class DeliveryType {
    DELIVERY,
    PICKUP
};

enum class PaymentType {
    CREDIT_CARD,
    NET_BANKING
};

// Helper functions to convert enums to strings (for display/logging)
inline string orderTimeTypeToString(OrderTimeType type) {
    switch(type) {
        case OrderTimeType::NOW: return "now";
        case OrderTimeType::SCHEDULE: return "schedule";
        default: return "unknown";
    }
}

inline string deliveryTypeToString(DeliveryType type) {
    switch(type) {
        case DeliveryType::DELIVERY: return "delivery";
        case DeliveryType::PICKUP: return "pickup";
        default: return "unknown";
    }
}

inline string paymentTypeToString(PaymentType type) {
    switch(type) {
        case PaymentType::CREDIT_CARD: return "creditcard";
        case PaymentType::NET_BANKING: return "netbanking";
        default: return "unknown";
    }
}

#endif // ORDER_ENUMS_H