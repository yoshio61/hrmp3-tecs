/*
 *  TOPPERS/HRMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      High Reliable Multiprocessing Profile Kernel
 * 
 *  Copyright (C) 2007-2019 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 * 
 *  上記著作権者は，以下の(1)～(4)の条件を満たす場合に限り，本ソフトウェ
 *  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
 *  変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *      の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
 *      と．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *        作権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
 *        報告すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 *      また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
 *      由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
 *      免責すること．
 * 
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
 *  に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
 *  アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
 *  の責任を負わない．
 * 
 *  $Id: spin_lock.h 12 2018-07-03 03:56:42Z ertl-honda $
 */

/*
 *		スピンロック機能
 */

#ifndef TOPPERS_SPIN_LOCK_H
#define TOPPERS_SPIN_LOCK_H

/*
 *  スピンロック初期化ブロック
 *
 *  lockフィールドは，スピンロックの実現方式毎に，異なる使い方をする．
 *
 *  ネイティブスピンロックの場合は，ターゲット定義で，ロック状態を保持
 *  する変数（または構造体）へのポインタか，ハードウェアで実現された排
 *  他制御機構を識別する番号（またはデバイスレジスタの番地）を格納する．
 *
 *  エミュレートされたスピンロックの場合は，スピンロック状態を表す
 *  bool_t型の変数へのポインタを格納する．
 */
typedef struct spin_lock_initialization_block {
	ATR			spnatr;			/* スピンロック属性 */
	intptr_t	lock;			/* ロック状態のためのデータ構造 */
	ACVCT		acvct;			/* アクセス許可ベクタ */
} SPNINIB;

/*
 *  スピンロックIDの最大値（kernel_cfg.c）
 */
extern const ID	tmax_spnid;

/*
 *  スピンロック初期化ブロックのエリア（kernel_cfg.c）
 */
extern const SPNINIB	spninib_table[];

/*
 *  スピンロック機能の初期化
 */
extern void	initialize_spin_lock(PCB *p_my_pcb);

/*
 *  スピンロックの強制解放
 *
 *  この関数は，CPUロック状態とCPUロック解除状態のいずれで呼んでもよい．
 *  ただし，タスクマイグレーションを避けるために，ディスパッチ保留状態
 *  で呼ばなければならない．この関数では，CPUロック状態を解除しない．
 */
extern void	force_unlock_spin(PCB *p_my_pcb);

#endif /* TOPPERS_SPIN_LOCK_H */
