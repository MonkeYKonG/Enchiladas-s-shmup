#pragma once

#include <list>
#include <vector>
#include <memory>
#include <utility>
#include <stdexcept>

namespace my
{
	//! Noeud d'un fichier XML. Correcpond � une balise et sont contenue.
	class XMLNode
	{
	public:
		typedef std::vector<std::shared_ptr<XMLNode> >	NodeList;
		typedef std::pair<std::string, std::string>  	NodeContent;
		typedef std::vector<NodeContent>			 	ContentList;
		typedef std::shared_ptr<XMLNode> XMLNodePtr;

		~XMLNode() noexcept {}

		//! Cr�er un nouveau noeud.
		static XMLNodePtr create() noexcept;
		//! Cr�er un nouveau noeud.
		/*!
		<b>Arguments</b><br/>
		name: le nom du noeud.<br/>
		contents: liste des attributs du noeud.
		*/
		static XMLNodePtr create(const std::string & name, const ContentList & contents) noexcept;

		//! Retourne la liste des noeuds enfants.
		const NodeList &GetChilds() const noexcept;
		//! Retourne l'enfant stocker � l'emplacement demand�.
		/*!
		<b>Arguments</b><br/>
		index: Index de l'enfant recherch�.
		<br/><br/>
		<b>Valeur de retour</b><br/>
		Retourne un pointeur sur l'enfant.
		<br/><br/>
		<b>Exception</b><br/>
		std::out_of_range: L'index pass� en argument n'existe pas.
		*/
		XMLNodePtr GetChild(int index) const throw (std::out_of_range);
		//! Retourne l'enfant ayant pour nom la chaine pass� en argument.
		/*!
		<b>Arguments</b><br/>
		key: Le nom de l'enfant recherch�.
		<br/><br/>
		<b>Valeur de retour</b><br/>
		Retorune l'enfant ayant pour nom key.
		<br/><br/>
		<b>Exception</b><br/>
		std::out_of_range: L'enfant recherch� n'existe pas.
		*/
		XMLNodePtr GetChild(const std::string & key) const throw (std::out_of_range);
		//! D�termine si un des enfant � pour nom la chaine pass� en argument.
		bool ChildExist(const std::string & key) const noexcept;
		//! Retourne le nom du noeud.
		const std::string &GetName() const noexcept;
		//! retourne la valeur du noeud.
		const std::string &GetValue() const noexcept;
		//! Retourne le tableau d'attributs du noeud.
		const ContentList &GetContents() const noexcept;
		//! Retourne l'attribut ayant pour cl� la chaine pass� en argument.
		/*!
		<b>Arguments</b><br/>
		key: nom de l'attribut recherch�.
		<br/><br/>
		<b>Valeur de retour</b><br/>
		Retourne l'attribut recherch�.
		<br/><br/>
		<b>Exception</b><br/>
		std::out_of_range: L'Attribut recherch� n'existe pas.
		*/
		const NodeContent &GetContent(const std::string & key) const throw (std::out_of_range);
		//! D�termine si un attribut du noeud a pour cl� la chaine pass� en argument.
		bool ContentExist(const std::string & key) const noexcept;
		//! Ajoute un nouveau noeaud � la liste d'enfants.
		/*!
		<b>Arguments</b><br/>
		newChild: Pointeur sur le noeud � ajouter.
		<br/><br/>
		<b>Exception</b><br/>
		std::invalid_argument: le noeud est un pointeur NULL.
		*/
		void AddChild(XMLNodePtr newChild) throw (std::invalid_argument);
		//! Change le nom deu noeud.
		void SetName(const std::string & name) noexcept;
		//! Change la valeur du noeud.
		void SetValue(const std::string & value) noexcept;
		//! Ajoute un attribut au tableau d'attributs du noeud.
		void AddAttribute(const NodeContent & attribute) noexcept;
		//! Ajoute un tableau d'attribut � la suite du tableau d'attribut du noeud.
		void AddAttributes(const ContentList & contents) noexcept;
		//! Retourne une chaine contenant le code XML du noeud.
		const std::string ToString() const noexcept;
		//! Modifie la valeur d'un attribut
		void SetAttribute(const NodeContent & attribute) throw (std::out_of_range);
		//! Remplace le tableau d'attribut par celui passer en arguments
		void SetAttributes(const ContentList & contents) noexcept;
		
	private:
		XMLNode() noexcept;
		XMLNode(const std::string & name, const ContentList & contents) noexcept;

		const std::string ToStringRec(const std::string & lineBegin) const noexcept;

		NodeList 	m_childs;
		std::string m_name;
		ContentList	m_contents;
		std::string	m_value;
	};
}