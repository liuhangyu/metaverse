/**
 * Copyright (c) 2011-2015 libbitcoin developers (see AUTHORS)
 * Copyright (c) 2016-2017 metaverse core developers (see MVS-AUTHORS)
 *
 * This file is part of metaverse-explorer.
 *
 * metaverse-explorer is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License with
 * additional permissions to the one published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version. For more information see LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <metaverse/explorer/commands/address-embed.hpp>

#include <iostream>
#include <metaverse/bitcoin.hpp>
#include <metaverse/explorer/define.hpp>
#include <metaverse/explorer/config/script.hpp>
#include <metaverse/explorer/utility.hpp>


namespace libbitcoin {
namespace explorer {
namespace commands {
using namespace bc::wallet;

console_result address_embed::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto& data = get_data_argument();
    const auto& version = get_version_option();

    // Create script from hash of data.
    const auto hashed = ripemd160_hash(data);
    const auto ops = chain::operation::to_pay_key_hash_pattern(hashed);
    const auto script = chain::script{ ops };

    // Make ripemd hash of serialized script.
    const auto hash = ripemd160_hash(script.to_data(false));
    
    // Make address (money sent here is lost forever).
    output << payment_address(hash, version) << std::flush;
    return console_result::okay;
}

} //namespace commands 
} //namespace explorer 
} //namespace libbitcoin 
