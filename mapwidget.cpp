#include "mapwidget.h"

extern Game *MainGame;
extern DataBase Data;
extern TcpNet *Network;
mapwidget::mapwidget(QWidget *parent) :
    QWidget(parent)
{
    fstream file;
    file.open("./MapInfo.dat",ios::in);

    MoveFlag=false;
    setGeometry(0,0,::MapWidth,::MapHeight);
    setAutoFillBackground(true);
    current=NULL;
    selected=NULL;
    int NumofRow=0;
    int NumofCol=0;
    int currentRow=0,currentCol=0;
    times=0.9;
    if(file!=NULL)
        file>>times;
    MapX=0;
    MapY=0;
    //setAttribute(Qt::WA_PaintOutsidePaintEvent);
    Map.load("./bfs.jpg");
    MapWidth = Map.width()*times;
    MapHeight = Map.height()*times;
    Map = Map.scaled(MapWidth,MapHeight,Qt::KeepAspectRatio);

    current=NULL;
    NumofCol=Map.width()/(3*linelength)*2-1;
    NumofRow=Map.height()/(2*shortll);
    MapWidth=NumofCol*1.5*linelength+linelength/2;
    MapHeight=NumofRow*2*shortll;

    for(int i=0;i<(NumofCol-1)/2*(NumofRow*2-1)+NumofRow;i++)
    {
        area * tmp=new area;
        if(file!=NULL)
        {
            int value;
            file>>value;
            tmp->iheight(value);
            file>>value;
            tmp->iareatype(value);
            tmp->setindex(i);
        }
        MapVect.push_back(*tmp);
    }
    file.close();
    vector<area>::iterator iter=MapVect.begin();
    for(currentCol=0;currentCol<NumofCol;currentCol++)
    {
        for(currentRow=0;currentRow<NumofRow-1;currentRow++,iter++)
        {
            if(currentRow>0)
            {
                iter->setLink(TOPTOP,&*(iter-1));
                (iter-1)->setLink(BOTTOMBOTTOM,&*iter);
            }
            if(currentCol>0)
            {
                if(currentCol%2==1)
                {
                    iter->setLink(TOPLEFT,&*(iter-NumofRow));
                    (iter-NumofRow)->setLink(BOTTOMRIGHT,&*iter);
                    iter->setLink(BOTTOMLEFT,&*(iter-NumofRow+1));
                    (iter-NumofRow+1)->setLink(TOPRIGHT,&*iter);
                }
                else
                {
                    if(currentRow>0)
                    {

                        iter->setLink(TOPLEFT,&*(iter-NumofRow));
                        (iter-NumofRow)->setLink(BOTTOMRIGHT,&*iter);
                    }
                    iter->setLink(BOTTOMLEFT,&*(iter-NumofRow+1));
                    (iter-NumofRow+1)->setLink(TOPRIGHT,&*iter);
                }
            }
        }
        if(currentCol%2==0)
        {
            iter->setLink(TOPTOP,&*(iter-1));
            (iter-1)->setLink(BOTTOMBOTTOM,&*iter);
            if(currentCol>0)
            {
                iter->setLink(TOPLEFT,&*(iter-NumofRow));
                (iter-NumofRow)->setLink(BOTTOMRIGHT,&*iter);
            }
            iter++;
        }
    }

    currentRow=currentCol=0;
    iter=MapVect.begin();
    qreal px=0,py=0,flag=0;
    while(px+linelength*1.5<=::MapWidth)
    {
        while(py+2*shortll<=::MapHeight)
        {
            myframe *mf=new myframe(this);
            mf->setGeometry(px,py,px+2*linelength,py+2*shortll);
            py+=2*shortll;
            mf->ptrToArea=&*(iter+currentRow);
            currentRow++;
            connect(mf,SIGNAL(MouseMoveon(myframe*)),this,SLOT(FocusChanged(myframe*)));
            connect(this,SIGNAL(MapMoving(int)),mf,SLOT(MapMoved(int)));
            connect(mf,SIGNAL(SelectaUnit(area*,int)),this,SLOT(SelectUnit(area*,int)));
        }
        if(!flag)
        {
            py=shortll;
            iter+=NumofRow;
        }
        else
        {
            py=0;
            iter+=NumofRow-1;
        }
        currentCol++;
        currentRow=0;
        flag=1-flag;
        px+=linelength*1.5;
    }
}

void mapwidget::mouseMoveEvent(QMouseEvent *)
{
    if(current)
    {
        current->setstate(0);
        current->repaint();
        //setMouseTracking(true);
       // QMessageBox::information(NULL, "Title", "Content", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
}

void mapwidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.drawPixmap(0,0,Map,MapX,MapY,-1,-1);
}

void mapwidget::MapMoved(int dir)
{
    switch(dir)
    {
    case TOP:
        if (MapY-2*shortll>=0)
        {
            MapY-=2*shortll;
            emit MapMoving(dir);
            repaint();
        }
        break;
    case BOTTOM:
        if (MapY+2*shortll+::MapHeight<=MapHeight)
        {
            MapY+=2*shortll;
            emit MapMoving(dir);
            repaint();
        }
        break;
    case LEFT:
        if (MapX-3*linelength>=0)
        {
            MapX-=3*linelength;
            emit MapMoving(dir);
            repaint();
        }
        break;
    case RIGHT:
        if (MapX+3*linelength+::MapWidth<=MapWidth)
        {
            MapX+=3*linelength;
            emit MapMoving(dir);
            repaint();
        }
        break;
    default:
        break;
    }
}

QPixmap mapwidget::getMap()
{
    return Map;
}

void mapwidget::FocusChanged(myframe *ptr)
{
    if(current)
    {
        current->setstate(0);
        current->repaint();
    }
    current=ptr;
    current->setstate(FOCUSON);
    current->repaint();
}

void mapwidget::SelectUnit(area* a,int cl)
{
    if(selected!=NULL&&selected->getUnits()==NULL)
        cl=RIGHT;
    if(!MoveFlag)
    if(cl==LEFT)
    {
        if(selected)
        {
            int num=0;
            UnitMove um;
            for(vector<unit>::iterator iter=selected->getUnits()->getUnitShell()->begin();iter<selected->getUnits()->getUnitShell()->end();iter++)
            {
                if(iter->getselected())
                {
                    num++;
                }
            }
            if((MainGame->getTurn()==MainGame->getSelf()->getIndex())&&a!=selected&&a->oreachornot()&&(a->getUnits()==NULL||!a->getsight()||a->getUnits()==NULL||num*selected->getUnits()->getUnitInfo().opopularity()+a->getUnits()->getUnitInfo().opopularity()*a->getUnits()->getUnitNum()<=6))
            {
                MoveFlag=true;
                //a->setUnits(selected->getUnits());
                //selected->setUnits(NULL);
                vector<area*> stack;
                area* tmp=a;
                while(tmp!=selected)
                {
                    stack.push_back(tmp);
                    tmp=tmp->getLastStep();
                }
                tmp=selected;
                UnitGroup *tmpunitgroup;
                tmpunitgroup=new UnitGroup;
                tmpunitgroup->setMovePoint(selected->getUnits()->getMovePoint());
                //if(a->getUnits()==NULL||num*selected->getUnits()->getUnitInfo().opopularity()+a->getUnits()->getUnitInfo().opopularity()*a->getUnits()->getUnitNum())
                int c=0;
                um.unitnum=0;
                for(vector<unit>::iterator iter=selected->getUnits()->getUnitShell()->begin();iter<selected->getUnits()->getUnitShell()->end();iter++,c++)
                {
                    if(iter->getselected())
                    {
                        um.unitindex[um.unitnum++]=c;
                        tmpunitgroup->getUnitShell()->push_back(*iter);
                        tmpunitgroup->incUnitNum();
                        selected->getUnits()->getUnitShell()->erase(iter);
                        selected->getUnits()->decUnitNum();
                        iter--;
                    }
                }
                if(!selected->getUnits()->getUnitNum())
                {
                    delete selected->getUnits();
                    selected->setUnits(NULL);
                }
                //tmpunitgroup=selected->getUnits();
               /* if(tmpunitgroup->getUnitNum())
                    emit PlaySound(MainGame->getSelf()->getIndex(),tmpunitgroup->getUnitInfo().oindex(),2);*/
                if(tmpunitgroup->getUnitNum())
                while(!stack.empty())
                {
                    if((*(stack.end()-1))->getUnits()!=NULL)
                    {
                        if((*(stack.end()-1))->getUnits()->getUnitInfo().omaster()!=MainGame->getSelf()->getIndex())
                            break;
                        else
                        {
                            while(!tmpunitgroup->getUnitShell()->empty())
                            {
                                (*(stack.end()-1))->getUnits()->getUnitShell()->push_back(*tmpunitgroup->getUnitShell()->begin());
                                (*(stack.end()-1))->getUnits()->incUnitNum();
                                tmpunitgroup->getUnitShell()->erase(tmpunitgroup->getUnitShell()->begin());
                            }
                            (*(stack.end()-1))->getUnits()->setMovePoint(qMin((*(stack.end()-1))->getUnits()->getMovePoint(),tmpunitgroup->getMovePoint()-1)+1);
                            delete tmpunitgroup;
                        }
                    }
                    else
                    {
                        (*(stack.end()-1))->setUnits(tmpunitgroup);
                    }
                    if(tmpunitgroup==tmp->getUnits())
                    {
                        tmp->setUnits(NULL);
                    }
                    if(MainGame->getMode()==ONLINE)
                    {
                        um.areaindex=tmp->getindex();
                        um.targetindex=(*(stack.end()-1))->getindex();
                        if(tmpunitgroup==tmp->getUnits())
                        {
                            um.unitnum=tmpunitgroup->getUnitNum();
                            for(int i=0;i<um.unitnum;i++)
                                um.unitindex[i]=i;
                        }
                        Network->sendMessage(um);
                    }
                    tmp->unselect();
                    tmp=*(stack.end()-1);
                    tmp->select();
                    stack.erase(stack.end()-1);
                    selected->unselect();
                    selected=tmp;
                    tmp->getUnits()->setMovePoint(tmp->getUnits()->getMovePoint()-1);
                    emit UnitSelected(tmp);
                    QEventLoop eventloop;
                    QTimer::singleShot(10, &eventloop, SLOT(quit()));
                    eventloop.exec();
                    if(setSight(selected))
                    {
                        cancelSight(selected->getLastStep());
                        break;
                    }
                    else
                        cancelSight(selected->getLastStep());
                }
                else
                    delete tmpunitgroup;
                setReachable();
            }
            else
            {
              if(MainGame->getTurn()==MainGame->getSelf()->getIndex()&&a->getattackable()&&selected->getUnits()->getMovePoint()>=0)
              {
                  fight(selected->getUnits(),a->getUnits());
                  selected->getUnits()->setMovePoint(-1);
                  if(a->getUnits()->getUnitNum()<=0)
                  {
                      delete a->getUnits();
                      a->setUnits(NULL);
                  }
                  //emit PlaySound(MainGame->getSelf()->getIndex(),selected->getUnits()->getUnitInfo().oindex(),3);
                  if(MainGame->getMode()==ONLINE)
                  {
                      struct UnitFight uf;
                      uf.areaindex=selected->getindex();
                      uf.targetindex=a->getindex();
                      if(a->getUnits()!=NULL)
                      {
                          uf.unitnum=a->getUnits()->getUnitNum();
                          for(int i=0;i<uf.unitnum;i++)
                          {
                              uf.unithp[i]=(*(a->getUnits()->getUnitShell()->begin()+i)).ohealthcurrent();
                              uf.unitshield[i]=(*(a->getUnits()->getUnitShell()->begin()+i)).oshieldcurrent();
                          }
                      }
                      else
                          uf.unitnum=0;
                      Network->sendMessage(uf);
                  }
              }
            selected->unselect();
            emit UnitSelected(NULL);
            selected=NULL;
            for(std::vector<area>::iterator iter=MapVect.begin();iter<MapVect.end();iter++)
            {
                iter->setflag(false);
                iter->ireachornot(0);
                iter->setattackable(0);
            }
            }
            MoveFlag=false;
            //repaint();
        }
        else
        {
        if(a->getUnits()!=NULL&&a->getsight())
        {
            selected=a;
            selected->select();
            if(selected->getUnits()->getUnitInfo().omaster()==MainGame->getSelf()->getIndex())
                //emit PlaySound(MainGame->getSelf()->getIndex(),selected->getUnits()->getUnitInfo().oindex(),1);
            emit UnitSelected(a);
            if(selected->getUnits()!=NULL&&selected->getUnits()->getUnitInfo().omaster()==MainGame->getSelf()->getIndex())
            {
                setReachable();
            }
            //repaint();
        }
        if(a->getUnits()==NULL&&(a->oareatype()==GAS||a->oareatype()==CRYSTAL))
        {
            selected=a;
            selected->select();
            emit UnitSelected(a);
        }
        }
    }
    else
    {
        if(selected)
            selected->unselect();
        else
        {
           // emit UnitSelected(a);
            //selected=a;
            //ProduceUnit(3);
        }
        selected=NULL;
        for(std::vector<area>::iterator iter=MapVect.begin();iter<MapVect.end();iter++)
        {
            iter->setflag(false);
            iter->ireachornot(0);
            iter->setattackable(0);
        }
        emit UnitSelected(NULL);
        //repaint();
    }
    emit refresh();
}

void mapwidget::setReachable()
{
    std::vector<area*> queue;
    for(std::vector<area>::iterator iter=MapVect.begin();iter<MapVect.end();iter++)
    {
        iter->setflag(false);
        iter->ireachornot(0);
        iter->setattackable(0);
    }
    if(selected!=NULL)
    {
        unit tmpunit;
        tmpunit=selected->getUnits()->getUnitInfo();
        queue.push_back(selected);
        selected->ireachornot(selected->getUnits()->getMovePoint());
        selected->setflag(true);
        while(!queue.empty())
        {
            area *currentarea;
            currentarea=*(queue.begin());
            queue.erase(queue.begin());
            for(int i=0;i<6;i++)
            {
                area *tmparea;
                tmparea=currentarea->getLink(i);
                if(currentarea->oreachornot()>0&&tmparea!=NULL&&!tmparea->getflag())
                {
                    if(tmparea->oareatype()!=INSKY&&(tmparea->oheight()-currentarea->oheight()<2)&&(tmparea->oheight()-currentarea->oheight()>-2)||(((tmparea->oheight()-currentarea->oheight()==2)||(tmparea->oheight()-currentarea->oheight()==-2))&&((selected->getUnits()->getUnitInfo().orace()==TERRAN&&selected->getUnits()->getUnitInfo().oindex()==4)||(selected->getUnits()->getUnitInfo().orace()==PROTOSS&&selected->getUnits()->getUnitInfo().oindex()==8))))
                    {
                       if(tmparea->getUnits()==NULL||!tmparea->getsight())
                       {
                           tmparea->ireachornot(currentarea->oreachornot()-1);
                           queue.push_back(tmparea);
                       }
                       else if(currentarea->oreachornot()>1&&tmparea->getUnits()->getUnitInfo().omaster()==MainGame->getSelf()->getIndex())
                           tmparea->ireachornot(-1);
                       tmparea->setflag(true);
                       tmparea->setLastStep(currentarea);
                    }
                }
            }
        }
    }
    if(selected->getUnits()->getMovePoint()>=0)
        setAttack();
}

void mapwidget::setAttack()
{
    for(std::vector<area>::iterator iter=MapVect.begin();iter<MapVect.end();iter++)
    {
        iter->setflag(false);
        iter->setdistance(0);
    }
    std::vector<area*> queue;
    queue.push_back(selected);
    while(!queue.empty())
    {
        area *currentarea;
        currentarea=*(queue.begin());
        queue.erase(queue.begin());
        for(int i=0;i<6;i++)
        {
            area *tmparea;
            tmparea=currentarea->getLink(i);
            if(currentarea->getdistance()<selected->getUnits()->getUnitInfo().olandstrrage()&&tmparea!=NULL&&!tmparea->getflag())
            {
                   tmparea->setdistance(currentarea->getdistance()+1);
                   tmparea->setflag(true);
                   if(tmparea->getsight()&&tmparea->getUnits()!=NULL&&tmparea->getUnits()->getUnitInfo().omaster()!=MainGame->getSelf()->getIndex())
                       tmparea->setattackable(1);
                   queue.push_back(tmparea);
            }
        }
    }
}

bool mapwidget::setSight(area* ar)
{
    bool flag=false;
    int sightrange=SIGHTRANGE;
    if(ar->oareatype()==LOOKOUT_TOWER)
        sightrange=LOOKTOWERSIGHT;
    for(std::vector<area>::iterator iter=MapVect.begin();iter<MapVect.end();iter++)
    {
        iter->setflag(false);
        iter->setdistance(0);
    }
    std::vector<area*> queue;
    queue.push_back(ar);
    while(!queue.empty())
    {
        area *currentarea;
        currentarea=*(queue.begin());
        queue.erase(queue.begin());
        for(int i=0;i<6;i++)
        {
            area *tmparea;
            tmparea=currentarea->getLink(i);
            if(currentarea->getdistance()<sightrange&&tmparea!=NULL&&!tmparea->getflag())
            {
                if(ar->oareatype()==LOOKOUT_TOWER||(ar->getUnits()!=NULL&&ar->getUnits()->getUnitInfo().orace()==PROTOSS&&ar->getUnits()->getUnitInfo().oindex()==8)||(tmparea->oheight()-ar->oheight()<2&&tmparea->oareatype()!=GRASS||(currentarea->oareatype()==GRASS&&tmparea->oareatype()==GRASS)))
                {
                   tmparea->setdistance(currentarea->getdistance()+1);
                   tmparea->setflag(true);
                   if(!tmparea->getsight())
                       if(tmparea->getUnits()!=NULL&&tmparea->getUnits()->getUnitInfo().omaster()!=MainGame->getSelf()->getIndex())
                           flag=true;
                   tmparea->incsight();
                   queue.push_back(tmparea);
                }
            }
        }
    }
    return flag;
}

void mapwidget::cancelSight(area* ar)
{
    int sightrange=SIGHTRANGE;
    if(ar->oareatype()==LOOKOUT_TOWER)
        sightrange=LOOKTOWERSIGHT;
    for(std::vector<area>::iterator iter=MapVect.begin();iter<MapVect.end();iter++)
    {
        iter->setflag(false);
        iter->setdistance(0);
    }
    std::vector<area*> queue;
    queue.push_back(ar);
    while(!queue.empty())
    {
        area *currentarea;
        currentarea=*(queue.begin());
        queue.erase(queue.begin());
        for(int i=0;i<6;i++)
        {
            area *tmparea;
            tmparea=currentarea->getLink(i);
            if(currentarea->getdistance()<sightrange&&tmparea!=NULL&&!tmparea->getflag())
            {
                if(tmparea->oheight()-ar->oheight()<2&&(tmparea->oareatype()!=GRASS&&currentarea->oareatype()!=GRASS))
                {
                   tmparea->setdistance(currentarea->getdistance()+1);
                   tmparea->setflag(true);
                   tmparea->decsight();
                   queue.push_back(tmparea);
                }
            }
        }
    }
}

void mapwidget::resetAllSight()
{
    for(std::vector<area>::iterator iter=MapVect.begin();iter<MapVect.end();iter++)
    {
        iter->resetsight();
    }
    for(std::vector<area>::iterator iter=MapVect.begin();iter<MapVect.end();iter++)
    {
        if(iter->getUnits()!=NULL&&iter->getUnits()->getUnitInfo().omaster()==MainGame->getSelf()->getIndex())
            setSight(&*iter);
    }
}

//我有两个UnitShell；分别为 UnitShellfir,UnitShellsec,设置每局5.5秒，m是每局攻击次数，m=5.5/olandstrspeed()

void mapwidget::fight(UnitGroup *UnitShellfir,UnitGroup *UnitShellsec)
{
std::vector<unit>::iterator iter1=UnitShellfir->getUnitShell()->begin();
std::vector<unit>::iterator iter2=UnitShellsec->getUnitShell()->begin();

int j,i,cishu,Num,sizefir,sizesec;
int landstrtype,landstr;
int def,deftype,race,healthcurrent,shieldcurrent;//护盾没有类型，只有值

sizefir=UnitShellfir->getUnitNum();
sizesec=UnitShellsec->getUnitNum();
race=iter2->orace();               //只有被打的种族，打的无关
cishu=5.5 / iter1->olandstrspeed();   //攻击次数
landstrtype=iter1->olandstrtype();
landstr=iter1->olandstr();
def=iter2->odef();
deftype=iter2->odeftype();


srand((unsigned)time(NULL));
j=rand()%2000+1;
Num=j-j/sizesec*sizesec;//随机挑出来的被打的逗比的序号
healthcurrent=(iter2+Num)->ohealthcurrent();
shieldcurrent=(iter2+Num)->oshieldcurrent();




if(race!=PROTOSS){//先看看被打的是不是神族
    if((landstrtype==2)&&(deftype==0)){
        landstr*=2;
    }
    else if((landstrtype==3)&&(deftype==1)){
        landstr*=2;
    }
    landstr-=def;//每条狗的攻击力
    landstr*=sizefir;//所有狗的总攻击力
    for(i=0;i<cishu;i++)
    if(sizesec){
        healthcurrent-=landstr;
        if(healthcurrent<=0){//如果死掉的话，删掉，并随机再拉出一条倒霉的狗
          if((iter2+Num)->oindex()!=-1)
          {
            MainGame->getEnemy()->incCurrentFood(-(iter2+Num)->opopularity());
            UnitShellsec->getUnitShell()->erase(iter2+Num);
          }
          else
          {
              UnitShellsec->getUnitShell()->clear();
              UnitShellsec->setUnitNum(1);
              sizesec=1;
          }
            j=rand()%2000+1;
            sizesec--;//数目减1
            if(sizesec)
            {
                Num=j-j/sizesec*sizesec;//随机挑出来的被打的逗比的序号
                healthcurrent=(iter2+Num)->ohealthcurrent();//新狗的血
            }
            UnitShellsec->decUnitNum();//真正的数目减1
        }
    }
    if(sizesec)
    (iter2+Num)->ihealthcurrent(healthcurrent);//此处本局结束时，侥幸未死的残血量应该返回
}

else{
    for(i=0;i<cishu;i++)
        if(sizesec){
      if(shieldcurrent>0){//还有护盾
        shieldcurrent-=landstr*sizefir;
        if ((shieldcurrent<0)&&(-shieldcurrent<def*sizefir))
            shieldcurrent=0;
        else
        if (shieldcurrent<0){
            healthcurrent+=shieldcurrent+def*sizefir;
            shieldcurrent=0;
        }
      }
      else
        healthcurrent-=(landstr-def)*sizefir;
      if(healthcurrent<=0){//如果死掉的话，删掉，并随机再拉出一条倒霉的狗
          if((iter2+Num)->oindex()!=-1)
          {
            MainGame->getEnemy()->incCurrentFood(-(iter2+Num)->opopularity());
            UnitShellsec->getUnitShell()->erase(iter2+Num);
          }
          else
          {
              UnitShellsec->getUnitShell()->clear();
              UnitShellsec->setUnitNum(1);
              sizesec=1;
          }
            j=rand()%2000+1;
            sizesec--;//数目减1
            if(sizesec)
            {
                Num=j-j/sizesec*sizesec;//随机挑出来的被打的逗比的序号
                healthcurrent=(iter2+Num)->ohealthcurrent();//新狗的血
                shieldcurrent=(iter2+Num)->oshieldcurrent();
            }
            UnitShellsec->decUnitNum();//真正的数目减1
      }
    }
    if(sizesec)
    {
    (iter2+Num)->ihealthcurrent(healthcurrent);//此处本局结束时，侥幸未死的残血量应该返回
    (iter2+Num)->ishieldcurrent(shieldcurrent);
    }
}
}

void mapwidget::reset()
{
    if(selected)
    {
        selected->unselect();
        selected=NULL;
    }
    for(std::vector<area>::iterator iter=MapVect.begin();iter<MapVect.end();iter++)
    {
        iter->setflag(false);
        iter->ireachornot(0);
        iter->setattackable(0);
        if(iter->getUnits()!=NULL)
            iter->getUnits()->setMovePoint(iter->getUnits()->getUnitInfo().omovespeed());
    }
    emit UnitSelected(NULL);
    repaint();
}

void mapwidget::ProduceUnit(int ind)
{
    unit tmp;
    if(ind!=1&&ind!=16&&ind!=-1)
        tmp=Data.getUnit(MainGame->getSelf()->getRace(),ind);
    else
    {
        if(ind!=-1)
            tmp=Data.getUnit(MainGame->getSelf()->getRace(),1);
        else
            tmp=Data.getUnit(MainGame->getSelf()->getRace(),-1);
    }
    if(MainGame->getTurn()==MainGame->getSelf()->getIndex())
    {
    if(tmp.ocrystalcost()<=MainGame->getSelf()->getCrystal()&&tmp.ogascost()<=MainGame->getSelf()->getGas()&&(tmp.opopularity()+MainGame->getSelf()->getCurrentFood()<=MainGame->getSelf()->getMaxFood()||ind==-1))
    {
        int i;
        int flag=1;
        for(i=0;i<6;i++)
        {
            flag=1;
            if(selected->getLink(i)->getUnits()==NULL||(selected->getLink(i)->getUnits()->getUnitInfo().oindex()==tmp.oindex()&&selected->getLink(i)->getUnits()->getUnitInfo().omaster()==MainGame->getSelf()->getIndex()&&(selected->getLink(i)->getUnits()->getUnitNum()+1)*tmp.opopularity()<=6))
                break;
            flag=0;
        }
        if(flag)
        {
            if(ind!=1&&ind!=16&&ind!=-1)
                MainGame->getSelf()->CreatUnit(selected->getLink(i),ind,1);
            else
                MainGame->getSelf()->CreatUnit(selected,ind,1);
            MainGame->getSelf()->incCrystal(-tmp.ocrystalcost());
            MainGame->getSelf()->incGas(-tmp.ogascost());
            if(ind!=-1)
                MainGame->getSelf()->incCurrentFood(tmp.opopularity());
            else
                MainGame->getSelf()->incMaxFood(tmp.opopularity());
            //emit PlaySound(MainGame->getSelf()->getIndex(),ind,0);
            if(MainGame->getMode()==ONLINE)
            {
                struct UnitProduce tmpup;
                if(ind!=1&&ind!=16&&ind!=-1)
                    tmpup.areaindex=selected->getLink(i)->getindex();
                else
                    tmpup.areaindex=selected->getindex();
                tmpup.unitindex=ind;
                Network->sendMessage(tmpup);
            }
            emit refresh();
        }
        else
        {
        }
    }
    else
    {
        /*if(tmp.ocrystalcost()>MainGame->getSelf()->getCrystal())
            emit PlaySound(MainGame->getSelf()->getRace(),0,0);
        else if(tmp.ogascost()>MainGame->getSelf()->getGas())
            emit PlaySound(MainGame->getSelf()->getRace(),0,1);
        else if(tmp.opopularity()+MainGame->getSelf()->getCurrentFood()>MainGame->getSelf()->getMaxFood())
            emit PlaySound(MainGame->getSelf()->getRace(),0,2);*/
    }
    }
    emit UnitSelected(selected);
    emit refresh();
}

void mapwidget::ReProduce(struct UnitProduce up)
{
    std::vector<area>::iterator iter;
    for(iter=MapVect.begin();iter<MapVect.end();iter++)
    {
        if(iter->getindex()==up.areaindex)
            break;
    }
    MainGame->getEnemy()->CreatUnit(&*iter,up.unitindex,1);
    repaint();
}

void mapwidget::ReMove(struct UnitMove um)
{
    std::vector<area>::iterator so;
    for(so=MapVect.begin();so<MapVect.end();so++)
    {
        if(so->getindex()==um.areaindex)
            break;
    }
    std::vector<area>::iterator ta;
    for(ta=MapVect.begin();ta<MapVect.end();ta++)
    {
        if(ta->getindex()==um.targetindex)
            break;
    }
    UnitGroup *tmpunitgroup;
    tmpunitgroup=new UnitGroup;
    int c=0,count=0;
    for(vector<unit>::iterator iter=so->getUnits()->getUnitShell()->begin();count<um.unitnum&&iter<so->getUnits()->getUnitShell()->end();iter++,c++)
    {
        if(c==um.unitindex[count])
        {
            tmpunitgroup->getUnitShell()->push_back(*iter);
            tmpunitgroup->incUnitNum();
            so->getUnits()->getUnitShell()->erase(iter);
            so->getUnits()->decUnitNum();
            iter--;
            c--;
        }
    }
    if(so->getUnits()->getUnitShell()->empty())
    {
        delete so->getUnits();
        so->setUnits(NULL);
    }
    if(ta->getUnits()!=NULL)
    {
            while(!tmpunitgroup->getUnitShell()->empty())
            {
                ta->getUnits()->getUnitShell()->push_back(*tmpunitgroup->getUnitShell()->begin());
                ta->getUnits()->incUnitNum();
                tmpunitgroup->getUnitShell()->erase(tmpunitgroup->getUnitShell()->begin());
            }
            delete tmpunitgroup;
    }
    else
    {
        ta->setUnits(tmpunitgroup);
    }
    emit refresh();
}

void mapwidget::ReFight(struct UnitFight uf)
{
    std::vector<area>::iterator so;
    for(so=MapVect.begin();so<MapVect.end();so++)
    {
        if(so->getindex()==uf.areaindex)
            break;
    }
    std::vector<area>::iterator ta;
    for(ta=MapVect.begin();ta<MapVect.end();ta++)
    {
        if(ta->getindex()==uf.targetindex)
            break;
    }
    MainGame->getSelf()->incCurrentFood((uf.unitnum-ta->getUnits()->getUnitNum())*ta->getUnits()->getUnitInfo().opopularity());
    if(uf.unitnum>0)
    {
        UnitGroup *tmpunitgroup;
        tmpunitgroup=new UnitGroup;
        unit NewUnit;
        NewUnit=ta->getUnits()->getUnitInfo();
        for(int i=0;i<uf.unitnum;i++)
        {
            tmpunitgroup->getUnitShell()->push_back(NewUnit);
            (tmpunitgroup->getUnitShell()->end()-1)->ihealthcurrent(uf.unithp[i]);
            (tmpunitgroup->getUnitShell()->end()-1)->ishieldcurrent(uf.unitshield[i]);
            tmpunitgroup->incUnitNum();
        }
        delete ta->getUnits();
        ta->setUnits(tmpunitgroup);
        ta->getUnits()->setMovePoint(NewUnit.omovespeed());
    }
    else
    {
      //  emit PlaySound(MainGame->getSelf()->getRace(),ta->getUnits()->getUnitInfo().oindex(),4);
        delete ta->getUnits();
        ta->setUnits(NULL);
    }
    /*if(ta->getUnits()->getUnitInfo().oindex()!=-1)
        emit PlaySound(MainGame->getSelf()->getRace(),0,4);
    else
        emit PlaySound(MainGame->getSelf()->getRace(),0,3);*/
    emit refresh();
}

void mapwidget::ReNewbase(struct NewBase nb)
{
    std::vector<area>::iterator iter;
    for(iter=MapVect.begin();iter<MapVect.end();iter++)
    {
        if(iter->getindex()==nb.areaindex)
            break;
    }
    MainGame->getEnemy()->CreatUnit(&*iter,-1,1);
}

void mapwidget::ReNewgame(struct NewGame ng)
{
    std::vector<area>::iterator so=MapVect.begin();
    std::vector<area>::iterator ta=MapVect.begin();
    for(std::vector<area>::iterator iter=MapVect.begin();iter<MapVect.end();iter++)
    {
        if(iter->getUnits()!=NULL)
            delete iter->getUnits();
        iter->setUnits(NULL);
        if(ta->getindex()!=ng.enemyareaindex)
            ta++;
        if(so->getindex()!=ng.selfareaindex)
            so++;
    }
    if(MainGame!=NULL)
        delete MainGame;
    ng.selfrace=1-ng.selfrace;
    ng.enemyrace=1-ng.enemyrace;
    ng.selfindex=1-ng.selfindex;
    ng.enemyindex=1-ng.enemyindex;
    MainGame=new Game(ng);
    MainGame->getSelf()->CreatUnit(&*ta,-1,1);
    MainGame->getEnemy()->CreatUnit(&*so,-1,1);
    selected=NULL;
    emit UnitSelected(NULL);
    emit refresh();
}

void mapwidget::clearMap()
{
    for(std::vector<area>::iterator iter=MapVect.begin();iter<MapVect.end();iter++)
    {
        if(iter->getUnits()!=NULL)
            delete iter->getUnits();
        iter->setUnits(NULL);
    }
    emit refresh();
}

area *mapwidget::getRandomBirthPoint()
{
    std::vector<area*> birtharea;
    int count=0;
    for(std::vector<area>::iterator iter=MapVect.begin();iter<MapVect.end();iter++)
    {
        if(iter->oareatype()==GAS&&iter->getUnits()==NULL)
        {
            birtharea.push_back(&*iter);
            count++;
        }
    }
    int ind;
    srand((unsigned)time(NULL));
    ind=rand()%count;
    return birtharea[ind];
}

void mapwidget::EndTurn()
{
    if(MainGame->getSelf()->getIndex()==MainGame->getTurn())
    for(std::vector<area>::iterator aiter=MapVect.begin();aiter<MapVect.end();aiter++)
    {
        if(aiter->getUnits()!=NULL&&aiter->getUnits()->getUnitInfo().omaster()==MainGame->getSelf()->getIndex()&&aiter->getUnits()->getUnitInfo().oindex()==-1)
        {
            int WorkerOnCrystal=0;
            int WorkerOnGas=0;
            for(std::vector<unit>::iterator iter=aiter->getUnits()->getUnitShell()->begin()+1;iter<aiter->getUnits()->getUnitShell()->end();iter++)
            {
                if(iter->getworkplace()==CRYSTAL)
                        WorkerOnCrystal++;
                    else
                        WorkerOnGas++;
            }
            if(WorkerOnCrystal>16)
                WorkerOnCrystal=16;
            if(WorkerOnGas>6)
                WorkerOnGas=6;
            MainGame->getSelf()->incCrystal(WorkerOnCrystal*50);
            MainGame->getSelf()->incGas(WorkerOnGas*50);
        }
    }
}

void mapwidget::BuildNewBase()
{
    ProduceUnit(-1);
}
