// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "txdb.h"
#include "main.h"
#include "uint256.h"


static const int nCheckpointSpan = 500;

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        (0,   uint256("0xecfb30eee1a53f304655e41022a6f6617922ad7faf84e1f1caacd315d303bbd8"))
        (1000,uint256("0x00000000000031a9a985985bd700bc8f5ed3bef65ae7e31078ecd64620871a26"))
        (5000,uint256("0x00000000000012fef3f09cdbd1c6f384e13ec51f31ac1595f237d389a9cd4f35"))
        (6355,uint256("0xe2b485a4530906429b6b983a5c698c6fcd710df0d78033fcad29305bc8d0e578"))
        (7700,uint256("0x000000000000bd29ccf625980b4e08ce31180d7e41a52a9db2567b73d5a3ab17"))
        (10000,uint256("0x000000000000565beb1a373fac4c4b36ae245688ec360a5b310182131df8a062"))
        (15000,uint256("0x0000000000006b6758975f919c3c389b949b69f877d3788a9e336ff788ca5635"))
        (20000,uint256("0x6dadfb7f142ca11b39217334d1877b0e00f6a9b8fc7270fc834e98021a5bb065"))
        (21356,uint256("0x04be0e9f73adcd7d5bc9c99ba8bef4959f68911bc0c565aca519294b43128f89"))
        (25000,uint256("0x2ebae56e706ce51609401205338ad54fe6e84aaba19a7b28ba0a388e25518407"))
        (30000,uint256("0xda0a287ae8d1c2235f6ba66b17fbf0fda677fed601ff38990f20435012498292"))
        (35000,uint256("0x0000000000004bf5b07e86463a2614fc70fb29ccb5961d26d966d0fe9e503e95"))
        (40000,uint256("0x00000000000002f0e390ec313d63b97247dbe1ccb81264d280fc93457c598c5a"))
        (45000,uint256("0x0000000000001a90e824aecd963e356738f5385f263aadfb3b79e7ff3100eed1"))
        (50000,uint256("0x00000000000021cf7cb8e8d8e079ce54149bb267c2e498a04c2bb3b3508a0912"))
        (55000,uint256("0x000000000000220af0cd7ad05764d59df79ce381326ab3c162c731500aef5512"))
        (60000,uint256("0xa5ecfb619c0397d0eee9b45ea0fc309c3ff745b68960af32a380116be15c30dd"))
        (70000,uint256("0x000000000000057449552ea96b4eb97a92ec169116a1dcb6a6a105a30fed6f37"))
    ;


    // TestNet has no checkpoints
    static MapCheckpoints mapCheckpointsTestnet;

    bool CheckHardened(int nHeight, const uint256& hash)
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        if (checkpoints.empty())
            return 0;
        return checkpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }

    // Automatically select a suitable sync-checkpoint
    const CBlockIndex* AutoSelectSyncCheckpoint()
    {
        const CBlockIndex *pindex = pindexBest;
        // Search backward for a block within max span and maturity window
        while (pindex->pprev && pindex->nHeight + nCheckpointSpan > pindexBest->nHeight)
            pindex = pindex->pprev;
        return pindex;
    }

    // Check against synchronized checkpoint
    bool CheckSync(int nHeight)
    {
        const CBlockIndex* pindexSync = AutoSelectSyncCheckpoint();

        if (nHeight <= pindexSync->nHeight)
            return false;
        return true;
    }
}
