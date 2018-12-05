#pragma once
#include "Effi.h"
#include "IRVisitor.h"
#include "EffiCompiledPipeline.h"

#include <unordered_map>
#include <utility>

namespace Nome
{

class CHLSLCodeGen : public IRVisitor
{
public:
	std::string CodeGen(IRExpr* node, const std::string& fnName);

	//Exprs
	void Visit(IRInputAttrVec3* node) override;
	void Visit(IRInputAttrVec4* node) override;
	void Visit(IRInputAttrMat3* node) override;
	void Visit(IRInputAttrMat4* node) override;
	void Visit(IRConstantFloat* node) override;
	void Visit(IRConstantVec3* node) override;
	void Visit(IRConstantVec4* node) override;
	void Visit(IRConstantMat3* node) override;
	void Visit(IRConstantMat4* node) override;
	void Visit(IRAdd* node) override;
	void Visit(IRMul* node) override;

	std::unordered_map<std::string, std::pair<EDataType, unsigned int>> ReferredFields;

private:
	std::string RetVal;
};

class CHLSLInputStructGen
{
public:
	CHLSLInputStructGen(const std::unordered_map<std::string, std::pair<EDataType, unsigned int>>& fields);

	std::string Result;
};

class CHLSLStructGen
{
public:
	CHLSLStructGen(const std::string& structName,
		const std::unordered_map<std::string, std::pair<EDataType, std::string>>& fields);

	std::string Result;
};

class CEffiCompiler : public IRVisitor
{
public:
	CEffiCompiler(CEffiContext* context) : EffiContext(context)
	{
	}

	void Compile(IRProgram* program);

	void GenericVisit(IRNode* node);

	//Exprs
	void Visit(IRExpr* node) override;
	void Visit(IRInputAttrVec3* node) override;
	void Visit(IRInputAttrVec4* node) override;
	void Visit(IRInputAttrMat3* node) override;
	void Visit(IRInputAttrMat4* node) override;
	void Visit(IRRef* node) override;
	void Visit(IRConstantFloat* node) override;
	void Visit(IRConstantVec3* node) override;
	void Visit(IRConstantVec4* node) override;
	void Visit(IRConstantMat3* node) override;
	void Visit(IRConstantMat4* node) override;
	void Visit(IRBinaryOp* node) override;
	void Visit(IRAdd* node) override;
	void Visit(IRMul* node) override;

	//Statments
	void Visit(IRStmt* node) override;
	void Visit(IRAssign* node) override;
	void Visit(IRMaterializeAttr* node) override;
	void Visit(IROffset* node) override;
	void Visit(IRSubdivideCC* node) override;

private:
	//Symbol table for vertix attributes
	std::unordered_map<std::string, IRExpr*> VSymTab;

	//Used to store the return value during expression evaluation
	IRExpr* RetExpr = nullptr;

	CEffiCompiledPipeline* CompiledPipeline = nullptr;

	CEffiContext* EffiContext;
};

} /* namespace Nome */