#include "GraphicsD3D9.h"
#include "GameWindow.h"
#include <algorithm>
#include <iostream>
struct Drawable
{
public:
	Drawable() {}
	Drawable(const Transform& transform, int textureID, const Rect& rect, float pixelsPerUnit, int sortingOrder, const ARGB& color) :
		transform(transform),
		textureID(textureID),
		rect(rect),
		pixelsPerUnit(pixelsPerUnit),
		sortingOrder(sortingOrder),
		color(color)
	{}
public:
	Transform transform;
	int textureID;
	Rect rect;
	float pixelsPerUnit;
	int sortingOrder;
	ARGB color;
};


bool GraphicsD3D9::Initialize()
{
	GameWindow window;
	window.CreateGameWindow(432, 360, 283, 84, "Metroid", WS_VISIBLE | WS_OVERLAPPEDWINDOW, "WindowClass");// WS_VISIBLE | WS_OVERLAPPED , 283, 84
	this->hWnd = window.handleWindow;

	isTextVisible = true;

	d3d = nullptr;
	d3ddev = nullptr;
	BackBufferWidth = window.windowWidth;//---------> import from game config
	BackBufferHeight = window.windowHeight;//--------> import from game config

	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	D3DPRESENT_PARAMETERS d3dpp = { 0 };
	d3dpp.Windowed = true;//--------> import from game config
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = this->hWnd;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferWidth = BackBufferWidth;
	d3dpp.BackBufferHeight = BackBufferHeight;
	d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, this->hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &d3ddev);
	D3DXCreateSprite(d3ddev, &D3DSprite);

	ZeroMemory(&desc, sizeof(D3DXFONT_DESC));
	desc.Height = 14;
	desc.Width = 14;
	desc.Weight = 500;
	desc.MipLevels = D3DX_DEFAULT;
	desc.Italic = false;
	desc.CharSet = 0;
	desc.OutputPrecision = 0;
	desc.Quality = 0;
	desc.PitchAndFamily = 0;
	strcpy_s(desc.FaceName, "Press Start 2P");
	D3DXCreateFontIndirect(d3ddev, &desc, &font);
	return true;
}

void GraphicsD3D9::SetTextVisibility(bool isVisible)
{
	isTextVisible = isVisible;
}

void GraphicsD3D9::Update()
{
	RenderBegin();
	RenderDrawQueue();
	RenderEnd();
}

bool GraphicsD3D9::Shutdown()
{
	if ((int)TextureIDMap.size() > 0)
	{
		std::map<int, LPDIRECT3DTEXTURE9>::iterator it;
		for (it = TextureIDMap.begin(); it != TextureIDMap.end(); it++)
		{
			(*it).second->Release();
			it++;
		}
	}
	TextureIDMap.clear();
	D3DSprite->Release();
	font->Release();
	d3ddev->Release();
	d3d->Release();
	return true;
}


void GraphicsD3D9::PrintText(const std::string & text, const Rect & rect)
{
	RECT textRect{ rect.left, rect.top, rect.right, rect.bottom };
	//font->DrawText(NULL, ("EN"), -1, &textRect, DT_LEFT | DT_NOCLIP, D3DCOLOR_XRGB(100, 176, 255));
	//font->DrawText(NULL, ("  .."), -1, &textRect, DT_LEFT | DT_NOCLIP, D3DCOLOR_XRGB(234, 158, 34));
	font->DrawText(NULL, (std::string("    ") + text).c_str(), -1, &textRect, DT_LEFT | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
}

bool GraphicsD3D9::CreateTextureFromFile(const std::string& fileName, const ARGB& colorKey, int textureID)
{
	LPDIRECT3DTEXTURE9 tex = nullptr;
	D3DXIMAGE_INFO info = { 0 };
	D3DXGetImageInfoFromFile(fileName.c_str(), &info);
	D3DXCreateTextureFromFileEx(
		d3ddev,
		fileName.c_str(),
		info.Width,
		info.Height,
		1,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_ARGB(colorKey.Alpha, colorKey.Red, colorKey.Green, colorKey.Blue),
		NULL,
		NULL,
		&tex);
	TextureIDMap.insert(std::pair<int, LPDIRECT3DTEXTURE9>(textureID, tex));
	return true;
}

void GraphicsD3D9::RemoveTexture(int textureID)
{
	LPDIRECT3DTEXTURE9 tex;
	std::map<int, LPDIRECT3DTEXTURE9>::iterator it = TextureIDMap.find(textureID);
	if (it != TextureIDMap.end())
	{
		tex = TextureIDMap.at(textureID);
		if (tex)
		{
			tex->Release();
			tex = nullptr;
		}
		TextureIDMap.erase(it);
	}
}

void GraphicsD3D9::GetImageInfoFromFile(const std::string& fileName, int & width, int & height)
{
	D3DXIMAGE_INFO info = { 0 };
	D3DXGetImageInfoFromFile(fileName.c_str(), &info);
	width = info.Width;
	height = info.Height;
}

void GraphicsD3D9::AddToDrawQueue(const Transform& transform, int textureID, const Rect & rect, float pixelsPerUnit, int sortingOrder, const ARGB& color)
{
	Drawable* drawable = new Drawable(transform, textureID, rect, pixelsPerUnit, sortingOrder, color);
	if ((int)DrawQueue.size() == 0)
	{
		DrawQueue.push_back(drawable);
		return;
	}
	else
	{
		if (DrawQueue.back()->sortingOrder <= sortingOrder)
		{
			DrawQueue.push_back(drawable);
			return;
		}
		if (DrawQueue.front()->sortingOrder > sortingOrder)
		{
			DrawQueue.push_front(drawable);
			return;
		}
		for (std::list<Drawable*>::iterator it = DrawQueue.begin(); it != DrawQueue.end(); ++it)
		{
			if ((*it)->sortingOrder >= sortingOrder)
			{
				DrawQueue.insert(it, drawable);
				return;
			}
		}
	}
}

void GraphicsD3D9::ClearDrawQueue()
{
	for (Drawable* drawable : DrawQueue)
	{
		if (drawable)
		{
			delete drawable;
			drawable = nullptr;
		}
	}
	DrawQueue.clear();
}

void GraphicsD3D9::RenderBegin()
{
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	d3ddev->BeginScene();
	D3DSprite->Begin(D3DXSPRITE_OBJECTSPACE | D3DXSPRITE_ALPHABLEND);
	d3ddev->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	d3ddev->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	d3ddev->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);
}

void GraphicsD3D9::RenderDrawQueue()
{
	for (Drawable* drawable : DrawQueue)
	{
		Draw(drawable->transform, drawable->textureID, drawable->rect, drawable->pixelsPerUnit, drawable->color);
	}

}

void GraphicsD3D9::Draw(const Transform& transform, int textureID, const Rect & rect, float pixelsPerUnit, const ARGB& color)
{
	if (pixelsPerUnit <= 0)  pixelsPerUnit = 1.0f;
	RECT D3DRect{ rect.left, rect.top, rect.right, rect.bottom };
	D3DXMATRIX transformMatrix;
	D3DXMatrixTransformation2D(&transformMatrix, NULL, NULL, &D3DXVECTOR2(transform.scale.x / pixelsPerUnit, -transform.scale.y / pixelsPerUnit), NULL, transform.rotation * D3DX_PI / 180.0f, &D3DXVECTOR2(transform.position.x, transform.position.y));
	D3DSprite->SetTransform(&transformMatrix);
	D3DSprite->Draw(TextureIDMap.at(textureID), &D3DRect, &D3DXVECTOR3((float)(D3DRect.right - D3DRect.left) / 2.0f, (float)(D3DRect.bottom - D3DRect.top) / 2.0f, 0.0f), NULL, D3DCOLOR_ARGB(color.Alpha, color.Red, color.Green, color.Blue));
}

void GraphicsD3D9::RenderEnd()
{
	D3DSprite->End();
	if (isTextVisible)
	{
		if (hpText.size() == 1)
		{
			PrintText((" " + hpText), Rect(50, 70, 50, 80));
		}
		else PrintText(hpText, Rect(50, 70, 50, 80));

		Rect rect = Rect(65, 100, 50, 80);
		RECT textRect{ rect.left, rect.top, rect.right, rect.bottom };
		if (rocketCountText.size() == 1)
		{
			font->DrawText(NULL, (("   00") + rocketCountText).c_str(), -1, &textRect, DT_LEFT | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
		}
		else if (rocketCountText.size() == 2)
		{
			font->DrawText(NULL, (("   0") + rocketCountText).c_str(), -1, &textRect, DT_LEFT | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
		}
		else if (rocketCountText.size() == 3)
		{
			font->DrawText(NULL, (("   ") + rocketCountText).c_str(), -1, &textRect, DT_LEFT | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
		}
		else font->DrawText(NULL, ("   "), -1, &textRect, DT_LEFT | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
	}

	d3ddev->EndScene();
	d3ddev->Present(NULL, NULL, NULL, NULL);
	ClearDrawQueue();

}

void GraphicsD3D9::SetViewPosition(const Vec2 & position)
{
	D3DXMATRIX viewMatrix;
	D3DXMatrixLookAtLH(&viewMatrix, &D3DXVECTOR3(position.x, position.y, 0.0f), &D3DXVECTOR3(position.x, position.y, 1.0f), &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	d3ddev->SetTransform(D3DTS_VIEW, &viewMatrix);
}

void GraphicsD3D9::SetViewSize(const Vec2 & viewSize)
{
	D3DXMATRIX orthoMatrix;
	D3DXMatrixOrthoLH(&orthoMatrix, viewSize.x, viewSize.y, 0.0f, 1.0f);
	d3ddev->SetTransform(D3DTS_PROJECTION, &orthoMatrix);
}

void GraphicsD3D9::SetViewport(unsigned long x, unsigned long y, unsigned long width, unsigned long height, float MinZ, float MaxZ)
{
	D3DVIEWPORT9 viewport;
	viewport.X = x;
	viewport.Y = y;
	viewport.Width = width;
	viewport.Height = height;
	viewport.MinZ = MinZ;
	viewport.MaxZ = MaxZ;
	d3ddev->SetViewport(&viewport);
}
