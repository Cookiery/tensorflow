/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

// This file defines the operations used in the XLA dialect.

#include "tensorflow/compiler/mlir/xla/ir/lhlo_ops.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/APInt.h"
#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Support/FormatVariadic.h"
#include "mlir/IR/Attributes.h"  // TF:local_config_mlir
#include "mlir/IR/Builders.h"  // TF:local_config_mlir
#include "mlir/IR/Dialect.h"  // TF:local_config_mlir
#include "mlir/IR/Location.h"  // TF:local_config_mlir
#include "mlir/IR/MLIRContext.h"  // TF:local_config_mlir
#include "mlir/IR/OpDefinition.h"  // TF:local_config_mlir
#include "mlir/IR/OpImplementation.h"  // TF:local_config_mlir
#include "mlir/IR/Operation.h"  // TF:local_config_mlir
#include "mlir/IR/OperationSupport.h"  // TF:local_config_mlir
#include "mlir/IR/PatternMatch.h"  // TF:local_config_mlir
#include "mlir/IR/StandardTypes.h"  // TF:local_config_mlir
#include "mlir/IR/TypeUtilities.h"  // TF:local_config_mlir
#include "mlir/IR/Types.h"  // TF:local_config_mlir
#include "mlir/IR/Value.h"  // TF:local_config_mlir
#include "tensorflow/compiler/mlir/xla/ir/lhlo_ops.h.inc"

namespace mlir {
namespace xla_lhlo {

XlaLhloDialect::XlaLhloDialect(MLIRContext* context)
    : Dialect(getDialectNamespace(), context) {
  addOperations<
#define GET_OP_LIST
#include "tensorflow/compiler/mlir/xla/ir/lhlo_ops.cc.inc"
      >();
}

#define GET_OP_CLASSES
#include "tensorflow/compiler/mlir/xla/ir/lhlo_ops.cc.inc"

// TODO(cheshire): Support folding, reuse code from hlo_ops.cc.

void FusionOp::build(Builder *builder, OperationState *result,
                     ArrayRef<NamedAttribute> attributes) {
  result->addAttributes(attributes);
  Region *bodyRegion = result->addRegion();
  FusionOp::ensureTerminator(*bodyRegion, *builder, result->location);
}

}  // namespace xla_lhlo
}  // namespace mlir
