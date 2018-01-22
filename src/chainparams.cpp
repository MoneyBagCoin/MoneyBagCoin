// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xb5;
        pchMessageStart[1] = 0x3c;
        pchMessageStart[2] = 0xd6;
        pchMessageStart[3] = 0xe2;
        vAlertPubKey = ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f");
        nDefaultPort = 43210;
        nRPCPort = 43211;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
        //
        // CBlock(hashBestChain=29d23d16f172fc92759cd3a2931f9023cbf416baff1031d6f664c0a454cc2a60  height=0  trust=1048577  date=12/03/17 18:57:16)
        //  Coinbase(hash=12630d16a9, nTime=1393221600, ver=1, vin.size=1, vout.size=1, nLockTime=0)
        //    CTxIn(COutPoint(0000000000, 4294967295), coinbase 00012a24323020466562203230313420426974636f696e2041544d7320636f6d6520746f20555341)
        //    CTxOut(empty)
        //  vMerkleTree: 12630d16a9
        const char *pszTimestamp = "💰💰💰💰💰💰💰💰💰 A lot of money bags will be found on next years 12/3/2017 2/22/2017 💰💰💰💰💰💰";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char *)pszTimestamp, (const unsigned char *)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1496692022, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1513900803;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 181489;

        hashGenesisBlock = genesis.GetHash();
        // printf("genesis.GetHash = %s\n", genesis.GetHash().ToString().c_str());
        // printf("merkle = %s\n", genesis.hashMerkleRoot.ToString().c_str());

        assert(hashGenesisBlock == uint256("0xecfb30eee1a53f304655e41022a6f6617922ad7faf84e1f1caacd315d303bbd8"));
        assert(genesis.hashMerkleRoot == uint256("0x2c473a492c11295d578a2f2409cb0401adf031bd29a5e963e38c2b55a3c16052"));

        vSeeds.push_back(CDNSSeedData("n0", "82.36.184.73:43210"));
        vSeeds.push_back(CDNSSeedData("n1", "5.189.152.63:43210"));
        vSeeds.push_back(CDNSSeedData("n2", "173.249.7.89:43210"));
        vSeeds.push_back(CDNSSeedData("n3", "138.68.68.149:43210"));
        vSeeds.push_back(CDNSSeedData("explorer", "35.197.91.231:43210"));
         vSeeds.push_back(CDNSSeedData("node-1", "35.205.164.239:43210"));
        vSeeds.push_back(CDNSSeedData("n3", "35.197.91.231:43210"));
        vSeeds.push_back(CDNSSeedData("n4", "147.135.130.119:43210"));
        vSeeds.push_back(CDNSSeedData("n5", "1.33.247.11:64765"));
        vSeeds.push_back(CDNSSeedData("n6", "1.54.213.25:25387"));
        vSeeds.push_back(CDNSSeedData("n7", "103.1.239.208:57179"));
        vSeeds.push_back(CDNSSeedData("n8", "103.233.194.202:60560"));
        vSeeds.push_back(CDNSSeedData("n9", "103.71.237.15:41447"));
        vSeeds.push_back(CDNSSeedData("n10", "104.155.199.216:53706"));
        vSeeds.push_back(CDNSSeedData("n11", "80.79.194.65:57371"));
        vSeeds.push_back(CDNSSeedData("n12", "104.155.199.216:55016"));
        vSeeds.push_back(CDNSSeedData("n13", "109.248.46.56:58755"));
        vSeeds.push_back(CDNSSeedData("n14", "111.239.150.36:61563"));
        vSeeds.push_back(CDNSSeedData("n15", "113.190.122.28:58802"));
        vSeeds.push_back(CDNSSeedData("n16", "115.132.163.13:56704"));
        vSeeds.push_back(CDNSSeedData("n17", "115.77.245.105:54707"));
        vSeeds.push_back(CDNSSeedData("n18", "119.59.115.39:59605"));
        vSeeds.push_back(CDNSSeedData("n18", "119.59.115.39:59605"));
        vSeeds.push_back(CDNSSeedData("n20", "119.59.115.40:43210"));


        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 51);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 5);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 165);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nLastPOWBlock = 250000;
    }

    virtual const CBlock &GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress> &FixedSeeds() const
    {
        return vFixedSeeds;
    }

  protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;

//
// Testnet
//

class CTestNetParams : public CMainParams
{
  public:
    CTestNetParams()
    {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x27;
        pchMessageStart[1] = 0x5c;
        pchMessageStart[2] = 0xd6;
        pchMessageStart[3] = 0xd9;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("");
        nDefaultPort = 43212;
        nRPCPort = 43213;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits = 0x1e0fffff; //504365055 Decimal Number
        genesis.nTime = 1512425803;
        genesis.nNonce = 2216093;

        //    assert(hashGenesisBlock == uint256("0x9acac6c7390427d4c6d658f4b9b520cb8c23977722783172bed3262b7a233cec));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 51);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 192);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        nLastPOWBlock = 0x7fffffff;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params()
{
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network)
{
    switch (network)
    {
    case CChainParams::MAIN:
        pCurrentParams = &mainParams;
        break;
    case CChainParams::TESTNET:
        pCurrentParams = &testNetParams;
        break;
    default:
        assert(false && "Unimplemented network");
        return;
    }
}

bool SelectParamsFromCommandLine()
{

    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet)
    {
        SelectParams(CChainParams::TESTNET);
    }
    else
    {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
