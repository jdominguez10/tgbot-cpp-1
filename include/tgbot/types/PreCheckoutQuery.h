//
// Created by Maks Mazurov (fox.cpp) on 21.05.17.
//

#ifndef TGBOT_PRECHECKOUTQUERY_H
#define TGBOT_PRECHECKOUTQUERY_H

#include <string>
#include <memory>
#include <vector>
#include "tgbot/types/User.h"
#include "tgbot/types/OrderInfo.h"

namespace TgBot {

/**
 * @brief This object contains information about an incoming pre-checkout query.
 *
 * https://core.telegram.org/bots/api#precheckoutquery
 * 
 * @ingroup types
 */
class PreCheckoutQuery {
public:
    typedef std::shared_ptr<PreCheckoutQuery> ptr;

    /**
     * @brief Unique query identifier.
     */
    std::string id;

    /**
     * @brief User who sent the query.
     */
    User::ptr from;

    /**
     * @brief Three-letter ISO 4217 currency code.
     */ 
    std::string currency;

    /** 
     * @brief Total price in the smallest units of the currency (integer,
     * not float/double). 
     * 
     * For example, for a price of US$ 1.45 pass 
     * amount = 145. See the exp parameter in currencies.json, it shows
     * the number of digits past the decimal point for each currency (2
     * for the majority of currencies).
     * 
     * https://core.telegram.org/bots/payments/currencies.json
     */
    int32_t total_amount;

    /**
     * @brief Bot specified invoice payload.
     */
    std::string invoice_payload;

    /**
     * @brief Optional. Identifier of the shipping option chosen by the user.
     */
    std::string shipping_option_id;

    /**
     * @brief Optional. Order info provided by the user.
     */
    OrderInfo::ptr order_info;
};
}

#endif //TGBOT_PRECHECKOUTQUERY_H