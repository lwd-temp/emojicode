//
//  ASTTypeExpr.cpp
//  Emojicode
//
//  Created by Theo Weidmann on 04/08/2017.
//  Copyright © 2017 Theo Weidmann. All rights reserved.
//

#include "ASTTypeExpr.hpp"
#include "Analysis/FunctionAnalyser.hpp"
#include "Types/TypeExpectation.hpp"

namespace EmojicodeCompiler {

Type ASTInferType::analyse(FunctionAnalyser *analyser, const TypeExpectation &expectation) {
    if (expectation.type() == TypeType::StorageExpectation || expectation.type() == TypeType::NoReturn) {
        throw CompilerError(position(), "Cannot infer ⚫️.");
    }
    type_ = expectation.copyType().unoptionalized();
    if (type_.type() == TypeType::Class) {
        availability_ = TypeAvailability::StaticAndAvailable;
    }
    return type_;
}

Type ASTTypeFromExpr::analyse(FunctionAnalyser *analyser, const TypeExpectation &expectation) {
    auto value = expr_->analyse(analyser, expectation);
    if (value.type() != TypeType::TypeAsValue) {
        throw CompilerError(position(), "Expected type value.");
    }
    return value.typeOfTypeValue();
}

Type ASTStaticType::analyse(FunctionAnalyser *analyser, const TypeExpectation &expectation) {
    return type_;
}

Type ASTThisType::analyse(FunctionAnalyser *analyser, const TypeExpectation &expectation) {
    return analyser->typeContext().calleeType();
}

}  // namespace EmojicodeCompiler