// Copyright (c) 2012-2018, The CryptoNote developers, The Bytecoin developers.
// Copyright (c) 2018 The Catalyst project
// Licensed under the GNU Lesser General Public License. See LICENSE for details.

#pragma once

#include <boost/variant.hpp>
#include <functional>
#include <vector>
#include "common/BinaryArray.hpp"
#include "crypto/types.hpp"

// We define here, as CryptoNoteConfig.h is never included anywhere anymore
#define catalyst_ALLOW_DEBUG_COMMANDS 1

namespace catalsyt {

using crypto::Hash;
using crypto::PublicKey;
using crypto::SecretKey;
using crypto::KeyPair;
using crypto::KeyDerivation;
using crypto::KeyImage;
using crypto::Signature;

using common::BinaryArray;

using namespace std::placeholders;  // We enjoy standard bindings

typedef uint32_t Height;
typedef uint64_t Difficulty;
typedef uint64_t Amount;
typedef uint32_t Timestamp;
typedef uint64_t UnlockMoment;
// Height or Timestamp, 32-bit is enough, but historically we already have several very large values in blockchain
typedef int64_t SignedAmount;

struct CoinbaseInput {
	Height block_index = 0;
};

struct KeyInput {
	Amount amount = 0;
	std::vector<uint32_t> output_indexes;
	KeyImage key_image;
};

struct KeyOutput {
	PublicKey key;
};

typedef boost::variant<CoinbaseInput, KeyInput> TransactionInput;

typedef boost::variant<KeyOutput> TransactionOutputTarget;

struct TransactionOutput {
	Amount amount = 0;
	TransactionOutputTarget target;
};

struct TransactionPrefix {
	uint8_t version          = 0;
	UnlockMoment unlock_time = 0;
	std::vector<TransactionInput> inputs;
	std::vector<TransactionOutput> outputs;
	BinaryArray extra;
};

struct Transaction : public TransactionPrefix {
	std::vector<std::vector<Signature>> signatures;
};

struct BaseTransaction : public TransactionPrefix {};  // has 'ignored' field during seria

struct ParentBlock {
	uint8_t major_version = 0;
	uint8_t minor_version = 0;
	Hash previous_block_hash;
	uint16_t transaction_count = 0;
	std::vector<Hash> base_transaction_branch;
	BaseTransaction base_transaction;
	std::vector<Hash> blockchain_branch;
};

struct BlockHeader {
	uint8_t major_version = 0;
	uint8_t minor_version = 0;
	uint32_t nonce        = 0;
	Timestamp timestamp   = 0;
	Hash previous_block_hash;
};

struct BlockTemplate : public BlockHeader {
	ParentBlock parent_block;
	Transaction base_transaction;
	std::vector<Hash> transaction_hashes;
};

struct AccountPublicAddress {
	PublicKey spend_public_key;
	PublicKey view_public_key;
};

struct SendProof {  // proofing that some tx actually sent amount to particular address
	Hash transaction_hash;
	AccountPublicAddress address;
	Amount amount = 0;
	std::string message;
	KeyDerivation derivation;
	Signature signature;
	// pair of derivation and signature form a proof of only fact that creator knows transaction private key and
	// he or she wished to include public view key of address into proof. To further check, look up tx_hash in
	// main chain and sum amounts of outputs which have spend keys corresponding to address public spend key
};

struct AccountKeys {
	AccountPublicAddress address;
	SecretKey spend_secret_key;
	SecretKey view_secret_key;
};

struct RawBlock {
	BinaryArray block;  // BlockTemplate
	std::vector<BinaryArray> transactions;
};

class Block {
public:
	BlockTemplate header;
	std::vector<Transaction> transactions;

	bool from_raw_block(const RawBlock &);
	bool to_raw_block(RawBlock &) const;
};

// Predicates for using in maps, sets, etc
inline bool operator==(const AccountPublicAddress &a, const AccountPublicAddress &b) {
	return std::tie(a.view_public_key, a.spend_public_key) == std::tie(b.view_public_key, b.spend_public_key);
}
inline bool operator!=(const AccountPublicAddress &a, const AccountPublicAddress &b) { return !operator==(a, b); }
inline bool operator<(const AccountPublicAddress &a, const AccountPublicAddress &b) {
	return std::tie(a.view_public_key, a.spend_public_key) < std::tie(b.view_public_key, b.spend_public_key);
}

}  // namespace catalyst

namespace seria {
class ISeria;

void ser(catalyst::Hash &v, ISeria &s);
void ser(catalyst::KeyImage &v, ISeria &s);
void ser(catalyst::PublicKey &v, ISeria &s);
void ser(catalyst::SecretKey &v, ISeria &s);
void ser(catalyst::KeyDerivation &v, ISeria &s);
void ser(catalyst::Signature &v, ISeria &s);

void ser_members(catalyst::AccountPublicAddress &v, ISeria &s);
void ser_members(catalyst::SendProof &v, ISeria &s);
void ser_members(catalyst::TransactionInput &v, ISeria &s);
void ser_members(catalyst::TransactionOutput &v, ISeria &s);
void ser_members(catalyst::TransactionOutputTarget &v, ISeria &s);

void ser_members(catalyst::CoinbaseInput &v, ISeria &s);
void ser_members(catalyst::KeyInput &v, ISeria &s);

void ser_members(catalyst::KeyOutput &v, ISeria &s);

void ser_members(catalyst::TransactionPrefix &v, ISeria &s);
void ser_members(catalyst::BaseTransaction &v, ISeria &s);
void ser_members(catalyst::Transaction &v, ISeria &s);

void ser_members(catalyst::BlockTemplate &v, ISeria &s);
void ser_members(catalyst::BlockHeader &v, ISeria &s);
void ser_members(catalyst::ParentBlock &v, ISeria &s);

void ser_members(catalyst::RawBlock &v, ISeria &s);
void ser_members(catalyst::Block &v, ISeria &s);
}
