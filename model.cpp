#include "model.h"

#include"mat.h"
#include"vec3.h"
#include"vec4.h"

CModel::CModel()
{
};

CModel::~CModel()
{
    fposition.clear();
    fnormal.clear();
    ftexture.clear();
};
void CModel::clear()
{
    CMeshPTNI::clear();
};

int CModel::read(const std::string& fileName)
{
    FILE *f;
    f = fopen(fileName.c_str(),"r");
    if(!f)return -1;
    float x,y,z;
    int iv,it,in,res;
    int n;
    int ch;
    int fw;
    int line=1;
    unsigned int outIndex=0;
    enum tmode
    {
        _end,_start,_hash,_f,_face,_g,_m,_s,_u,_v,_o,
        _position,_preTex,_preNorm,_tex,_norm,_err=-1
    }mode=_start;

    fposition.clear();
    ftexture.clear();
    fnormal.clear();

    do
    {
        ch=fgetc(f);
        if(ch=='\n')
        {
            line++;
            mode=_start;
        }else if(mode==_start)
        {
            switch(ch)
            {
            case ' ':
            case '\r':
                mode = _start;
                break;
            case '#':
                mode = _hash;
                break;
            case 'f':
                mode = _f;
                break;
            case 'g':
                mode = _g;
                break;
            case 'o':
                mode = _o;
                break;
            case 'm':
                mode = _m;
                break;
            case 's':
                mode = _s;
                break;
            case 'u':
                mode = _u;
                break;
            case 'v':
                mode = _v;
                break;
            case -1:
                mode=_end;
                break;
            default:
                return -line;
            }
        }else
        switch(mode)
        {
        case _f:
            if(ch==' ') mode = _face;
            else return _err;
            break;
        case _v:
            switch(ch)
            {
            case ' ':
                mode = _position;
                break;
            case 't':
                mode = _preTex;
                break;
            case 'n':
                mode = _preNorm;
                break;
            default:
                return _err;
            }
            break;
        case _preTex:
            if(ch==' ')mode=_tex;
            else return _err;
            break;
        case _preNorm:
            if(ch==' ')mode=_norm;
            else return _err;
            break;
        default:
            break;
        }
        switch(mode)
        {
        case _position:
            n=fscanf(f,"%f %f %f",&x,&y,&z);
            fposition.push_back(x);
            fposition.push_back(y);
            fposition.push_back(z);
            if(n!=3)mode=_err;

            else mode=_start;
            break;
        case _tex:
            n=fscanf(f,"%f %f",&x,&y);
            fscanf(f,"%f",&z); //pick off possible third tex coord
            ftexture.push_back(x);
            ftexture.push_back(y);
            if(n!=2)mode=_err;
            else mode=_start;
            break;
        case _norm:
            n=fscanf(f,"%f %f %f",&x,&y,&z);
            fnormal.push_back(x);
            fnormal.push_back(y);
            fnormal.push_back(z);
            if(n!=3)mode=_err;
            else mode=_start;
            break;
        case _face:
            fw=0;
            do{
                iv=readNumber(f);
                if(iv<0){mode=_err;break;};
                res=fgetc(f);
                if(res!='/')
                {
                    mode=_err;
                    break;
                }
                it=readNumber(f);
                if(it<0)
                {
                    fseek(f,-1,SEEK_CUR);
                    it=0;
                }
                res=fgetc(f);
                if(res!='/')
                {
                    fseek(f,-1,SEEK_CUR);
                    in=0;
                }else
                {
                    in=readNumber(f);
                    if(in<0)
                    {
                        fseek(f,-1,SEEK_CUR);
                        in=0;
                    }
                }
                res=fgetc(f);
                ///////////////////////////////////////////////////
                if(fw>2) //for faces with more than 3 sides add triangles
                {
                    size_t s;
                    s = oposition.size();
                    oposition.push_back(oposition[s-3*fw  ]);     //x0
                    oposition.push_back(oposition[s-3*fw+1]);     //y0
                    oposition.push_back(oposition[s-3*fw+2]);     //z0
                    oposition.push_back(oposition[s-3]);        //x1
                    oposition.push_back(oposition[s-2]);        //y1
                    oposition.push_back(oposition[s-1]);        //z1
                    onormal.push_back(onormal[s-3*fw  ]);         //nx0
                    onormal.push_back(onormal[s-3*fw+1]);         //ny0
                    onormal.push_back(onormal[s-3*fw+2]);         //nz0
                    onormal.push_back(onormal[s-3]);            //nx1
                    onormal.push_back(onormal[s-2]);            //ny1
                    onormal.push_back(onormal[s-1]);            //nz1
                    s = otexture.size();
                    otexture.push_back(otexture[s-2*fw  ]);      //tu0
                    otexture.push_back(otexture[s-2*fw+1]);      //tv0
                    otexture.push_back(otexture[s-2]);           //tu0
                    otexture.push_back(otexture[s-1]);           //tv0
                    otriangleIndex.push_back(outIndex++);   // idx
                    otriangleIndex.push_back(outIndex++);   // idx
                }
                oposition.push_back(fposition[3*iv-3]); // x
                oposition.push_back(fposition[3*iv-2]); // y
                oposition.push_back(fposition[3*iv-1]); // z
                if((3*in-1)>fnormal.size())      //no normals in file
                {
                    onormal.push_back(0);
                    onormal.push_back(1);
                    onormal.push_back(0);
                }else
                {
                    onormal.push_back(fnormal[3*in-3]);     // nx
                    onormal.push_back(fnormal[3*in-2]);     // ny
                    onormal.push_back(fnormal[3*in-1]);     // nz
                }
                if((2*it-1)>ftexture.size())      //texture values absent
                {
                    otexture.push_back(0);
                    otexture.push_back(0);
                }else
                {
                    otexture.push_back(  ftexture[2*it-2]); // u
                    otexture.push_back(1-ftexture[2*it-1]); // v
                }
                otriangleIndex.push_back(outIndex++);   // idx
                fseek(f,-1,SEEK_CUR);
                res=fgetc(f);
                fw++;
            }while(res==' ');
            fseek(f,-1,SEEK_CUR);
            mode=_start;
            break;
        case _hash:
        case _g:
        case _m:
        case _o:
        case _s:
        case _u:
            while((ch=fgetc(f))!='\n');
            mode=_start;
            fseek(f,-1,SEEK_CUR);
            break;
        default:
            break;
        }
    }while((ch>0)&&(mode!=_err));
    fclose(f);
    if(mode==_err)
        return -line;
    return mode;
}
///////////////////////////////////////////////////////////////////////////////
//
int CModel::write(const char *fName)
{
    FILE *f;
    f = fopen(fName,"w");
    if(!f)return -1;

    for(unsigned int i=0;i<oposition.size();i+=3)
        fprintf(f,"v %f %f %f\n",oposition[i],oposition[i+1],oposition[i+2]);
    fprintf(f,"\n");

    for(unsigned int i=0;i<onormal.size();i+=3)
        fprintf(f,"vn %f %f %f\n",onormal[i],onormal[i+1],onormal[i+2]);
    fprintf(f,"\n");

    for(unsigned int i=0;i<otexture.size();i+=2)
        fprintf(f,"vt %f %f\n",otexture[i],otexture[i+1]);
    fprintf(f,"\n");

    for(unsigned int i=0;i<otriangleIndex.size()/3;i++)
    {
        fprintf(f,"f ");
        for(unsigned j=0;j<3;j++)
            fprintf(f,"%u/%u/%u ",i*3+j+1,i*3+j+1,i*3+j+1);
        fprintf(f,"\n");  
    };

    fclose(f);
}
///////////////////////////////////////////////////////////////////////////////
//
void CModel::info()
{
    std::cout << "fposition=" << fposition.size() << std::endl;
    std::cout << "fnormal=" << fnormal.size() << std::endl;
    std::cout << "ftexture=" << ftexture.size() << std::endl;
    std::cout << std::endl;
    CMeshPTNI::info();
}

int CModel::readNumber(FILE *f)
{
    int acc,n;
    do{n=fgetc(f);}while(n==' ');
    acc=n-'0';
    if((acc<0)||(acc>9))return -1;
    do{
        acc*=10;
        n=fgetc(f);
        acc+=n-'0';
    }while((n>='0')&&(n<='9'));
    acc=(acc+'0'-n)/10;
    fseek(f,-1l,SEEK_CUR);
    return acc;
}
