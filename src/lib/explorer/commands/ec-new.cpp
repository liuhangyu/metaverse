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
#include <metaverse/explorer/commands/ec-new.hpp>

#include <iostream>
#include <metaverse/bitcoin.hpp>
#include <metaverse/explorer/define.hpp>
#include <metaverse/explorer/utility.hpp>
#include <metaverse/explorer/config/ec_private.hpp>



// The BX_EC_NEW_INVALID_KEY condition is not covered by test.
// This is because is not known what seed will produce an invalid key.
namespace libbitcoin {
namespace explorer {
namespace commands {

console_result ec_new::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const data_chunk& seed = get_seed_argument();

    if (seed.size() < minimum_seed_size)
    {
        error << BX_EC_NEW_SHORT_SEED << std::flush;
        return console_result::failure;
    }

    ec_secret secret(new_key(seed));
    if (secret == null_hash)
    {
        error << BX_EC_NEW_INVALID_KEY << std::flush;
        return console_result::failure;
    }

    // We don't use bc::ec_private serialization (WIF) here.
    output << config::ec_private(secret) << std::flush;
    return console_result::okay;
}

} //namespace commands 
} //namespace explorer 
} //namespace libbitcoin 
