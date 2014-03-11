// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    // How many times we expect transactions after the last checkpoint to
    // be slower. This number is a compromise, as it can't be accurate for
    // every system. When reindexing from a fast disk with a slow CPU, it
    // can be up to 20, while when downloading from a slow network with a
    // fast multicore CPU, it won't be much higher than 1.
    static const double fSigcheckVerificationFactor = 5.0;

    struct CCheckpointData {
        const MapCheckpoints *mapCheckpoints;
        int64 nTimeLastCheckpoint;
        int64 nTransactionsLastCheckpoint;
        double fTransactionsPerDay;
    };

    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
            (  0, hashGenesisBlock )
            (2,     uint256("0x6f8d257348ef0c1f579f3693ffa6476bcf801e6ac4c74de8317dc39da92bdbd2"))
            (3,     uint256("0xb2d5648320770adf33069804ccc009947543d5f4d6b83ad56d814157bea44bc6"))
            (2,     uint256("0x6f8d257348ef0c1f579f3693ffa6476bcf801e6ac4c74de8317dc39da92bdbd2"))
            (8,     uint256("0x9f8f6b2ae11604131abd4d5ff0b39d2ed8519e16dfe911778dfec6356cf65d90"))
            (25,    uint256("0x081b1fabdb94f98cd15dd4ab1e97bc634ba484973794dfc121284fccc70fb014"))
            (26,    uint256("0x102190e258609398c032de01ba66b28ac6970e24f4b5f77810d96853a6e65b65"))
            (39,    uint256("0xdd49b0b4ec6d242f02d53e2e5799339932451c7f7bede8eab9b98ed217494251"))
            (44,    uint256("0x93360c9841b526e6948296c560f423ec6c965620f761ef92682d92131ac02ac8"))
            (71,    uint256("0xd41f24ea11d9ee373e8f773a39bf82233e5a8ae7450396da08a4a46dfeeb7769"))
            (121,   uint256("0x7a9313768b7c9e5c1cc6ceab6ff88f51f98e10a3690f34a88c2761d5b66ba06e"))
            (200,   uint256("0x109e4b201c383c6027158a7d47e920a427433dd5788ce23d0bd8fba03927efc9"))
            (255,   uint256("0x1205a3efa1e63201220c7235bf827026cc4b296ee6b85842ae68515963bf162b"))
            (853,   uint256("0x6eff35ed6d1ff0d168d6e2d129dced88204c7d95f25f8df64ab8cc2971fc073c"))
            (1965,  uint256("0x3dd138210d6887945e0b781eff08020b4d2c9165ff3a536902a4b309f18c97dc"))
            (1983,  uint256("0x396a0b09dc0de17f2b39b83633c2fd8133a9a594fe55e57e8dda593a5b8cedc5"))
            (1991,  uint256("0xe1b05a2faf2a8af14d199f23793520cd68462005d648c576000fb451a4304f29"))
            (2659,  uint256("0x209110f7e8d7680930ece8e74b4798555c621a43e8a8bd4d64d6d0067061940e"))
            (2989,  uint256("0x2b1098121686dea0c8e421b8169358158d7ccd4eebfbf6d7407021c850c293c3"))
            (3900,  uint256("0x9587837996c39c00346e96204ac817b209538ef7861fef8ab0f4064c5594193d"))
            (3961,  uint256("0x85519e2b4cd1b0327bd850e522abc962e95bb1ef0bfe637cb8e58cad9e2b1a1d"))
            (4826,  uint256("0x8350936b4fd6e0569530eb5cefa36167bbd971cfc625dc9f9b8243fa83240645"))
            (5622,  uint256("0xbf015a3acc9230a384bd87fc4a848c94ba0325fd3b37490324134a4c34261377"))
            (6524,  uint256("0x78af056bc4cdd37eefd7c2068191d0cb1179747b5325c9030501f5865e07c962"))
            (6739,  uint256("0xd667eb79b6b32901a1e3688aebae9fb5a970c3f943a12167bebbe6201f468654"))
            (7707,  uint256("0xab9130d37e665ec0b5a659b4b0c1ee4f148931ad11290879df52bdae0d50131a"))
            (8929,  uint256("0xbe5ee63b2214ff746226d757a203458291ce3e5c8cd8706cefc224bfed5e84f0"))
            (9757,  uint256("0x249a118dd9c9c73c53a70471f3117fd787f0124e105815c261ba9d0652b434ac"))
            (11372, uint256("0x2d73a7da6b9009d1adfc8f83e12bc439c79295f15a3f411e0c4e8b1ab8cb5917"))
            (11695, uint256("0x36f581aae80ab0aed333307d7b7f9a5498d765b8dd9ef0fddeacb1cf23ab95b7"))
            (11756, uint256("0xd8c71a76bfefe4c9673d45f9ca7a84f96f93b2653a0fe847a4b5c0a80667fe6a"))
            (15806, uint256("0x7ba75cbc87f11c83acb9fad9561cd893ba2c4716e15c9076a37fd2d279a8855e"))
            (16244, uint256("0x14af2d3a906a0f40730d5643ff358f56275d212c0bd8e2a3f6a458a46c632b8c"))
            (21758, uint256("0x5081d35e9dd7b24df2f55c3684057a85937629f19dd208db6b89c7fb114da921"))
            (21822, uint256("0x44f31abceac19b5f8ea0568c1f098495996edde70df43fb8e457075a4f465269"))
            (23259, uint256("0xd36ea10e9444462aa6c97194de5df016de5539e46667b526a5024b2a0cfde646"))
            (26286, uint256("0x323fdb28c7f11255273c254004f9eac168fcea184a0ee1442dfef4fd9a0e1e75"))
            (28921, uint256("0x568d730f0515db21bde3b0d16ac5af46886a622cab76f351fba26f24885eb967"))
            (31399, uint256("0x26821e5267a4699041d2ec62ab8f88dca6c15f1970ec2cff286c812518810b48"))
            (31950, uint256("0xbb5668b9730e65ce784e491b445ef4f19a1b76aea0e47de1445d5ab307ebd736"))
            (60000, uint256("0x3d3857fa9edb5739362df87241cb539c88689567bbf12b3fd8cf4eac47f22521"))

        ;
    static const CCheckpointData data = {
        &mapCheckpoints,
        1392233509, // * UNIX timestamp of last checkpoint block
        12491,   // * total number of transactions between genesis and last checkpoint
                    //   (the tx=... number in the SetBestChain debug.log lines)
        60000.0     // * estimated number of transactions per day after checkpoint
    };

    static MapCheckpoints mapCheckpointsTestnet = 
        boost::assign::map_list_of
            ( 0,uint256("0x6031650e6a6e1ec11e6d7871ccf93d06375469cf08f565d9fc5a0079e4ad92e3"))
        ;
    static const CCheckpointData dataTestnet = {
        &mapCheckpointsTestnet,
        1389221120,
        1,
        2100
    };

    const CCheckpointData &Checkpoints() {
        if (fTestNet)
            return dataTestnet;
        else
            return data;
    }

    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (!GetBoolArg("-checkpoints", true))
            return true;
		return true;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end()) return true;
        return hash == i->second;
    }

    // Guess how far we are in the verification process at the given block index
    double GuessVerificationProgress(CBlockIndex *pindex) {
        if (pindex==NULL)
            return 0.0;
		return 0.0;

        int64 nNow = time(NULL);

        double fWorkBefore = 0.0; // Amount of work done before pindex
        double fWorkAfter = 0.0;  // Amount of work left after pindex (estimated)
        // Work is defined as: 1.0 per transaction before the last checkoint, and
        // fSigcheckVerificationFactor per transaction after.

        const CCheckpointData &data = Checkpoints();

        if (pindex->nChainTx <= data.nTransactionsLastCheckpoint) {
            double nCheapBefore = pindex->nChainTx;
            double nCheapAfter = data.nTransactionsLastCheckpoint - pindex->nChainTx;
            double nExpensiveAfter = (nNow - data.nTimeLastCheckpoint)/86400.0*data.fTransactionsPerDay;
            fWorkBefore = nCheapBefore;
            fWorkAfter = nCheapAfter + nExpensiveAfter*fSigcheckVerificationFactor;
        } else {
            double nCheapBefore = data.nTransactionsLastCheckpoint;
            double nExpensiveBefore = pindex->nChainTx - data.nTransactionsLastCheckpoint;
            double nExpensiveAfter = (nNow - pindex->nTime)/86400.0*data.fTransactionsPerDay;
            fWorkBefore = nCheapBefore + nExpensiveBefore*fSigcheckVerificationFactor;
            fWorkAfter = nExpensiveAfter*fSigcheckVerificationFactor;
        }

        return fWorkBefore / (fWorkBefore + fWorkAfter);
    }

    int GetTotalBlocksEstimate()
    {
		return 0;
        if (!GetBoolArg("-checkpoints", true))
            return 0;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        return checkpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
		return NULL;
        if (!GetBoolArg("-checkpoints", true))
            return NULL;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }
}
