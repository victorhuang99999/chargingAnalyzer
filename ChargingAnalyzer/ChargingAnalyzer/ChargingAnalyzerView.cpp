
// ChargingAnalyzerView.cpp : CChargingAnalyzerView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "ChargingAnalyzer.h"
#endif

#include "ChargingAnalyzerDoc.h"
#include "ChargingAnalyzerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChargingAnalyzerView

IMPLEMENT_DYNCREATE(CChargingAnalyzerView, CView)

BEGIN_MESSAGE_MAP(CChargingAnalyzerView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CChargingAnalyzerView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CChargingAnalyzerView 构造/析构

CChargingAnalyzerView::CChargingAnalyzerView()
{
	// TODO: 在此处添加构造代码

}

CChargingAnalyzerView::~CChargingAnalyzerView()
{
}

BOOL CChargingAnalyzerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CChargingAnalyzerView 绘制

void CChargingAnalyzerView::OnDraw(CDC* /*pDC*/)
{
	CChargingAnalyzerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CChargingAnalyzerView 打印


void CChargingAnalyzerView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CChargingAnalyzerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CChargingAnalyzerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CChargingAnalyzerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CChargingAnalyzerView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CChargingAnalyzerView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CChargingAnalyzerView 诊断

#ifdef _DEBUG
void CChargingAnalyzerView::AssertValid() const
{
	CView::AssertValid();
}

void CChargingAnalyzerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CChargingAnalyzerDoc* CChargingAnalyzerView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CChargingAnalyzerDoc)));
	return (CChargingAnalyzerDoc*)m_pDocument;
}
#endif //_DEBUG


// CChargingAnalyzerView 消息处理程序
