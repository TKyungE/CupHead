#include "Image.h"
#pragma comment(lib,"msimg32.lib")

HRESULT Image::Init(int width, int height)
{
    HDC hdc = GetDC(g_hWnd);

    imageInfo = new IMAGE_INFO();
    imageInfo->resID = 0;
    imageInfo->hMemDC = CreateCompatibleDC(hdc);
    imageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
    imageInfo->hOldBit = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);

    imageInfo->hTempDC = CreateCompatibleDC(hdc);
    imageInfo->hTempBit = CreateCompatibleBitmap(hdc, width, height);
    imageInfo->hOldTemp = (HBITMAP)SelectObject(imageInfo->hTempDC, imageInfo->hTempBit);

 
    imageInfo->width = width;
    imageInfo->height = height;
    imageInfo->loadType = IMAGE_LOAD_TYPE::Empty;

    ReleaseDC(g_hWnd, hdc);

    if (imageInfo->hBitmap == NULL)
    {
        Release();
        return E_FAIL;
    }

    return S_OK;   // S_OK, E_FAIL
}

HRESULT Image::Init(const wchar_t* filePath, int width, int height, 
    bool isTransparent, COLORREF transColor)
{
    HDC hdc = GetDC(g_hWnd);

    imageInfo = new IMAGE_INFO();
    imageInfo->resID = 0;
    imageInfo->hMemDC = CreateCompatibleDC(hdc);
    imageInfo->hBitmap = (HBITMAP)LoadImage(
        g_hInstance, filePath, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
    imageInfo->hOldBit = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);

    imageInfo->hTempDC = CreateCompatibleDC(hdc);
    imageInfo->hTempBit = CreateCompatibleBitmap(hdc, width, height);
    imageInfo->hOldTemp = (HBITMAP)SelectObject(imageInfo->hTempDC, imageInfo->hTempBit);


    imageInfo->width = width;
    imageInfo->height = height;
    imageInfo->loadType = IMAGE_LOAD_TYPE::File;

    imageInfo->maxFrameX = 0;
    imageInfo->maxFrameY = 0;
    imageInfo->frameWidth = 0;
    imageInfo->frameHeight = 0;
    imageInfo->currFrameX = imageInfo->currFrameY = 0;

    ReleaseDC(g_hWnd, hdc);

    if (imageInfo->hBitmap == NULL)
    {
        Release();
        return E_FAIL;
    }

    this->isTransparent = isTransparent;
    this->transColor = transColor;

    return S_OK;   // S_OK, E_FAIL
}

HRESULT Image::Init(const wchar_t* filePath, int width, int height, int maxFrameX, int maxFrameY, bool isTransparent, COLORREF transColor)
{
    HDC hdc = GetDC(g_hWnd);

    imageInfo = new IMAGE_INFO();
    imageInfo->resID = 0;
    imageInfo->hMemDC = CreateCompatibleDC(hdc);
    imageInfo->hBitmap = (HBITMAP)LoadImage(
        g_hInstance, filePath, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
    imageInfo->hOldBit = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);

    imageInfo->width = width;
    imageInfo->height = height;
    imageInfo->loadType = IMAGE_LOAD_TYPE::File;

    imageInfo->maxFrameX = maxFrameX;
    imageInfo->maxFrameY = maxFrameY;
    imageInfo->frameWidth = width / maxFrameX;
    imageInfo->frameHeight = height / maxFrameY;
    imageInfo->currFrameX = imageInfo->currFrameY = 0;

    imageInfo->hTempDC = CreateCompatibleDC(hdc);
    imageInfo->hTempBit = CreateCompatibleBitmap(hdc, width, height);
    imageInfo->hOldTemp = (HBITMAP)SelectObject(imageInfo->hTempDC, imageInfo->hTempBit);


    ReleaseDC(g_hWnd, hdc);
    
    if (imageInfo->hBitmap == NULL)
    {
        Release();
        return E_FAIL;
    }

    this->isTransparent = isTransparent;
    this->transColor = transColor;

    return S_OK;   // S_OK, E_FAIL
}

void Image::Render(HDC hdc, int destX, int destY)
{
    if (isTransparent)
    {
        GdiTransparentBlt(hdc,
            destX, destY,
            imageInfo->width, imageInfo->height,
            imageInfo->hMemDC,
            0, 0,
            imageInfo->width, imageInfo->height,
            transColor);
    }
    else
    {
        BitBlt(
            hdc,                // 복사 목적지 DC
            destX, destY,       // 복사 목적지 위치
            imageInfo->width,   // 원본에서 복사될 가로크기
            imageInfo->height,  // 원본에서 복사될 세로크기
            imageInfo->hMemDC,  // 원본 DC
            0, 0,               // 원본 복사 시작 위치
            SRCCOPY             // 복사 옵션
        );
    }
}

void Image::Render(HDC hdc, int destX, int destY, int frameIndex, bool isFlip)
{
    imageInfo->currFrameX = frameIndex;

    if (isFlip && isTransparent)
    {
        StretchBlt(imageInfo->hTempDC, 0, 0,
            imageInfo->frameWidth, imageInfo->frameHeight,
            imageInfo->hMemDC,
            (imageInfo->frameWidth * imageInfo->currFrameX) + (imageInfo->frameWidth - 1),
            imageInfo->frameHeight * imageInfo->currFrameY,
            -imageInfo->frameWidth, imageInfo->frameHeight,
            SRCCOPY
        );

        GdiTransparentBlt(hdc,
            destX, destY,
            imageInfo->frameWidth, imageInfo->frameHeight,

            imageInfo->hTempDC,
            0, 0,
            imageInfo->frameWidth, imageInfo->frameHeight,
            transColor);
    }
    else if (isTransparent)
    {
        GdiTransparentBlt(hdc,
            destX, destY,
            imageInfo->frameWidth, imageInfo->frameHeight,

            imageInfo->hMemDC,
            imageInfo->frameWidth * imageInfo->currFrameX,
            imageInfo->frameHeight * imageInfo->currFrameY,
            imageInfo->frameWidth, imageInfo->frameHeight,
            transColor);
    }
    else
    {
        BitBlt(
            hdc,
            destX, destY,
            imageInfo->width / 9,
            imageInfo->height,
            imageInfo->hMemDC,
            imageInfo->width / 9 * frameIndex, 0,
            SRCCOPY
        );
    }
}

void Image::FrameRenderLoop(HDC hdc, int destX, int destY,
    int frameX, int frameY, bool isFlip, bool isLoop)
{
    if (!isLoop)
    {
        FrameRender(hdc, destX, destY, frameX, frameY, isFlip);
        return;
    }

    int width = imageInfo->frameWidth;
    FrameRender(hdc, destX, destY, frameX, frameY, isFlip);
    FrameRender(hdc, destX + width, destY, frameX, frameY, isFlip);
}

void Image::FrameRender(HDC hdc, int destX, int destY, 
    int frameX, int frameY, bool isFlip)
{
    int x = destX - (imageInfo->frameWidth / 2);
    int y = destY - (imageInfo->frameHeight / 2);

    imageInfo->currFrameX = frameX;
    imageInfo->currFrameY = frameY;

    if (isFlip && isTransparent)
    {
        StretchBlt(imageInfo->hTempDC, 0, 0,
            imageInfo->frameWidth, imageInfo->frameHeight,
            imageInfo->hMemDC,
            (imageInfo->frameWidth * imageInfo->currFrameX) + (imageInfo->frameWidth - 1),
            imageInfo->frameHeight * imageInfo->currFrameY,
            -imageInfo->frameWidth, imageInfo->frameHeight,
            SRCCOPY
        );

        GdiTransparentBlt(hdc,
            x, y,
            imageInfo->frameWidth, imageInfo->frameHeight,

            imageInfo->hTempDC,
            0, 0,
            imageInfo->frameWidth, imageInfo->frameHeight,
            transColor);
    }
    else if (isTransparent)
    {
        GdiTransparentBlt(hdc,
            x, y,
            imageInfo->frameWidth, imageInfo->frameHeight,
            imageInfo->hMemDC,
            imageInfo->frameWidth * imageInfo->currFrameX,
            imageInfo->frameHeight * imageInfo->currFrameY,
            imageInfo->frameWidth, imageInfo->frameHeight,
            transColor);
    }
    else
    {
        BitBlt(
            hdc,
            x, y,
            imageInfo->frameWidth,
            imageInfo->frameHeight,
            imageInfo->hMemDC,
            imageInfo->frameWidth * imageInfo->currFrameX, 
            imageInfo->frameHeight * imageInfo->currFrameY,
            SRCCOPY
        );
    }
}

void Image::FrameRenderAlpha(HDC hdc, int destX, int destY, int frameX, int frameY, bool _IsOver, int _AlphaValue, COLORREF _AlphaColor, bool isFlip)
{
    if (true == _IsOver)
    {
        FrameRender(hdc, destX, destY, frameX, frameY, isFlip);
    }

    int x = destX - (imageInfo->frameWidth / 2);
    int y = destY - (imageInfo->frameHeight / 2);

    imageInfo->currFrameX = frameX;
    imageInfo->currFrameY = frameY;

    BITMAPINFO bmi = { 0 };
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = imageInfo->frameWidth;
    bmi.bmiHeader.biHeight = -imageInfo->frameHeight; // DIB는 기본적으로 상하 반전
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32; // 32bit (ARGB)
    bmi.bmiHeader.biCompression = BI_RGB;

    void* pBits = nullptr;
    imageInfo->hTempBit = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, &pBits, NULL, 0);
    SelectObject(imageInfo->hTempDC, imageInfo->hTempBit);
    BitBlt(imageInfo->hTempDC, 0, 0, imageInfo->frameWidth, imageInfo->frameHeight, imageInfo->hMemDC, imageInfo->frameWidth * frameX, imageInfo->frameHeight * frameY, SRCCOPY);

    // 3. 픽셀 데이터 직접 수정 (투명색을 완전 투명하게 변환)
    DWORD* pixels = (DWORD*)pBits;
    COLORREF transColor32 = (0x00FFFFFF & transColor); // RGB 값만 사용

    for (int i = 0; i < imageInfo->frameWidth * imageInfo->frameHeight; i++)
    {
        if ((pixels[i] & 0x00FFFFFF) == transColor32) // 투명색이면
        {
            pixels[i] = 0x00000000; // 완전 투명 (ARGB = 0x00000000)
        }
        else
        {
            //pixels[i] |= 0xFF000000;
            //pixels[i] |= 0xFFFFFFFF; // 알파값 255로 설정 (불투명),
            if (true == _IsOver)
            {
                pixels[i] |= (0xFF000000 | _AlphaColor); // 알파값 255로 설정 (불투명),
            }

            else
            {
                pixels[i] |= 0xFF000000; // 알파값 255로 설정 (불투명),
            }
          
        }
    }

    // 4. 알파 블렌드 설정
    BLENDFUNCTION bf;
    bf.BlendOp = AC_SRC_OVER;
    bf.BlendFlags = 0;
    bf.SourceConstantAlpha = _AlphaValue;  // 밝기 조절 (0 ~ 255)
    bf.AlphaFormat = AC_SRC_ALPHA;  // 알파 채널 사용

    AlphaBlend(hdc, x, y, imageInfo->frameWidth, imageInfo->frameHeight, imageInfo->hTempDC, 0, 0, imageInfo->frameWidth, imageInfo->frameHeight, bf);
    DeleteObject(imageInfo->hTempBit);
}

void Image::Release()
{
    if (imageInfo)
    {
        SelectObject(imageInfo->hTempDC, imageInfo->hOldTemp);
        DeleteObject(imageInfo->hTempBit);
        DeleteDC(imageInfo->hTempDC);

        SelectObject(imageInfo->hMemDC, imageInfo->hOldBit);
        DeleteObject(imageInfo->hBitmap);
        DeleteDC(imageInfo->hMemDC);

        delete imageInfo;
        imageInfo = nullptr;
    }
}
