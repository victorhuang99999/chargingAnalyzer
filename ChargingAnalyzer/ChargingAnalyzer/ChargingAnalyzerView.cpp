
// ChargingAnalyzerView.cpp : CChargingAnalyzerView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CChargingAnalyzerView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CChargingAnalyzerView ����/����

CChargingAnalyzerView::CChargingAnalyzerView()
{
	// TODO: �ڴ˴���ӹ������

}

CChargingAnalyzerView::~CChargingAnalyzerView()
{
}

BOOL CChargingAnalyzerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CChargingAnalyzerView ����

void CChargingAnalyzerView::OnDraw(CDC* /*pDC*/)
{
	CChargingAnalyzerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CChargingAnalyzerView ��ӡ


void CChargingAnalyzerView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CChargingAnalyzerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CChargingAnalyzerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CChargingAnalyzerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
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


// CChargingAnalyzerView ���

#ifdef _DEBUG
void CChargingAnalyzerView::AssertValid() const
{
	CView::AssertValid();
}

void CChargingAnalyzerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CChargingAnalyzerDoc* CChargingAnalyzerView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CChargingAnalyzerDoc)));
	return (CChargingAnalyzerDoc*)m_pDocument;
}
#endif //_DEBUG


// CChargingAnalyzerView ��Ϣ�������
