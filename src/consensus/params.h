// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2016 The BICOScoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BICOSCOIN_CONSENSUS_PARAMS_H
#define BICOSCOIN_CONSENSUS_PARAMS_H

#include "uint256.h"
#include "verify.h"
#include <map>
#include <string>

namespace Consensus {

enum DeploymentPos
{
    DEPLOYMENT_TESTDUMMY,
    DEPLOYMENT_CSV, // Deployment of BIP68, BIP112, and BIP113.
    DEPLOYMENT_SEGWIT, // Deployment of BIP141, BIP143, and BIP147.
    // NOTE: Also add new deployments to VersionBitsDeploymentInfo in versionbits.cpp
    MAX_VERSION_BITS_DEPLOYMENTS
};

/**
 * Struct for each individual consensus rule change using BIP9.
 */
struct BIP9Deployment {
    /** Bit position to select the particular bit in nVersion. */
    int bit;
    /** Start MedianTime for version bits miner confirmation. Can be a date in the past */
    int64_t nStartTime;
    /** Timeout/expiry MedianTime for the deployment attempt. */
    int64_t nTimeout;
};

/**
 * Parameters that influence chain consensus.
 */
struct Params {
    uint256 hashGenesisBlock;
    int nSubsidyHalvingInterval;
    /** Block height and hash at which BIP34 becomes active */
    int BIP34Height;
    uint256 BIP34Hash;
    /** Block height at which BIP65 becomes active */
    int BIP65Height;
    /** Block height at which BIP66 becomes active */
    int BIP66Height;
    /** Block height at which BICOScoin GPU hard fork becomes active */
    //int BCSHeight;
    /** Block height at which Zawy's LWMA difficulty algorithm becomes active */
    int BCSZawyLWMAHeight;
    /** Block height at which Equihash<144,5> becomes active */
    int BCSEquihashForkHeight;
    /** Limit BICOSCOIN_MAX_FUTURE_BLOCK_TIME **/
    int64_t BCSMaxFutureBlockTime;
    /** Premining blocks for BICOScoin GPU hard fork **/
    //int BCSPremineWindow;
    //bool BCSPremineEnforceWhitelist;
    /**
     * Minimum blocks including miner confirmation of the total of 2016 blocks in a retargeting period,
     * (nPowTargetTimespan / nPowTargetSpacing) which is also used for BIP9 deployments.
     * Examples: 1916 for 95%, 1512 for testchains.
     */
    uint32_t nRuleChangeActivationThreshold;
    uint32_t nMinerConfirmationWindow;
    BIP9Deployment vDeployments[MAX_VERSION_BITS_DEPLOYMENTS];
    /** Proof of work parameters */
    uint256 powLimit;
    uint256 powLimitLegacy;
    uint256 powLimitStart;
    
    const uint256& PowLimit(bool postfork) const { return postfork ? powLimit : powLimitLegacy; }
    bool fPowAllowMinDifficultyBlocks;
    bool fPowNoRetargeting;
    int64_t nPowTargetSpacing;
    int64_t nPowTargetTimespanLegacy;
    int64_t DifficultyAdjustmentInterval() const { return nPowTargetTimespanLegacy / nPowTargetSpacing; }
    uint256 nMinimumChainWork;
    uint256 defaultAssumeValid;
    
    // Params for Digishield difficulty adjustment algorithm. (Used by mainnet currently.)
    int64_t nDigishieldAveragingWindow;
    int64_t nDigishieldMaxAdjustDown;
    int64_t nDigishieldMaxAdjustUp;
    int64_t DigishieldAveragingWindowTimespan() const { return nDigishieldAveragingWindow * nPowTargetSpacing; }
    int64_t DigishieldMinActualTimespan() const {
        return (DigishieldAveragingWindowTimespan() * (100 - nDigishieldMaxAdjustUp)) / 100;
    }
    int64_t DigishieldMaxActualTimespan() const {
        return (DigishieldAveragingWindowTimespan() * (100 + nDigishieldMaxAdjustDown)) / 100;
    }

    // Params for Zawy's LWMA difficulty adjustment algorithm. (Used by testnet and regtest)
    int64_t nZawyLwmaAveragingWindow;  // N
    int64_t nZawyLwmaAjustedWeight;  // k = (N+1)/2 * 0.9989^(500/N) * T

    CBlockHeaderSignatureValidation SignatureValidation;
};
} // namespace Consensus

#endif // BICOSCOIN_CONSENSUS_PARAMS_H
