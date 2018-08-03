/*
* ��������� ���״�� �������� ����մϴ�
* ���ӽý��� ����� �ʼ����γ�
* ��¼�� ���� �˴� �������̽����� �����ϰԵ�. ������ ������ �ʹ� Specific ������ ������ �ִ����
*/

#pragma once
#include "MnGameSystemModule.h"

namespace MNL
{
	//����μ� AddQueue ���� ���� �������̽��� Ŭ����
	class MnRenderable
	{
	public:
		virtual ~MnRenderable() = default;
	};

	class MnRenderer
	{
	public:
		virtual ~MnRenderer() = default;
		virtual void Render(const std::shared_ptr<MnRenderable>& spRenderable);
	};

	class MnRenderModule : public MnGameSystemModule
	{
	public:
		virtual ~MnRenderModule() = default;
	public:
		//�������̽����� �����Ѵ�
		virtual void AddQueue(const std::shared_ptr<MnRenderable>& spRenderable) = 0;
		virtual void Render() = 0;

	};

}