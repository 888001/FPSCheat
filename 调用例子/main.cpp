#include"GameCheat.h"
#pragma comment(lib,"��ҿ�.lib")

DWORD pid=0;
UINT64 ģ���ַ, �����ַ;
vector<UINT64> TempArray,��������, �ؾ�����, ��Ʒ����, ��Ʒ������, ��Ͷ����;
HANDLE hProcess;
HWND hwnd;

RGBA BoxColor{ 200, 200, 10, 255 };
RGBA LineColor{ 0, 0, 139, 255 };
RGBA TextColor{ 139, 0, 0, 255 };
RGBA CircleColor{ 0, 139, 139, 255 };

bool ���Ʒ��� = true;
bool �������� = true;
bool ������Ʒ = true;


static bool alpha_preview = true;
static bool alpha_half_preview = false;
static bool drag_and_drop = true;
static bool options_menu = true;
static bool hdr = false;
ImGuiColorEditFlags misc_flags = (hdr ? ImGuiColorEditFlags_HDR : 0) | (drag_and_drop ? 0 : ImGuiColorEditFlags_NoDragDrop) | (alpha_half_preview ? ImGuiColorEditFlags_AlphaPreviewHalf : (alpha_preview ? ImGuiColorEditFlags_AlphaPreview : 0)) | (options_menu ? 0 : ImGuiColorEditFlags_NoOptions);

void GetData()
{
	while (1)
	{
		//�����ȡ�������� �ȷŵ�TempArray��֮���ٷ���������飬�����ڶ�ȡ��ʱ����ܳ���
		��������.clear();
		for (vector<UINT64>::iterator it = TempArray.begin(); it != TempArray.end(); it++)
			��������.push_back(*it);
	}
}

void Draw()
{
	UINT64 �����ַ;
	Rect rect;
	for (int i=0;i<��������.size();i++)
	{
		if(i<��������.size())	�����ַ =��������[i];

		WorldToScreen(hProcess, �����ַ, �����ַ, 1.8, &rect, true);
		if(���Ʒ���) DrawBox(rect.x, rect.y, rect.w, rect.h, BoxColor,2);
		if(��������) DrawLine(MyImGui::win_width / 2, 0, rect.x, rect.y, LineColor, 2);
	}
}

void DrawMenu()
{
	static ImVec4 color = ImVec4(200.0/255.0,200.0/255.0,10.0/255.0,1);
	//ImGui::ShowDemoWindow(&ShowImGui);
	if (ImGui::CollapsingHeader(u8"����ѡ��"))
	{
		ImGui::Checkbox(u8"���Ʒ���", &���Ʒ���);
		ImGui::Checkbox(u8"��������", &��������); ImGui::SameLine(150);
		ImGui::Checkbox(u8"������Ʒ", &������Ʒ); ImGui::SameLine(300);
		ImGui::ColorEdit4(u8"������ɫ", (float*)&color, ImGuiColorEditFlags_Float | misc_flags);
		ImGui::ColorEdit4(u8"������ɫ", (float*)&color, ImGuiColorEditFlags_Float | misc_flags);
	}
}

int main()
{
	pid=GetProcessIdByName(L"LdVBoxHeadless.exe");
	hwnd = FindWindowExW(FindWindowW(NULL,L"�׵�ģ����"),NULL,L"RenderWindow",L"TheRender");
	hProcess=MyOpenProcess(PROCESS_ALL_ACCESS,false,pid);

	cout << "PID:" << pid << endl;
	cout << "���ھ��:" << hwnd <<endl;

	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)GetData, NULL, 0, NULL);
	//ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_FirstUseEver);
	CreateWindowAndInitImGui(hwnd, Draw, DrawMenu);

	return 0;
}