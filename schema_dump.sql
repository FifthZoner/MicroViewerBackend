--
-- PostgreSQL database dump
--

-- Dumped from database version 17.5 (Debian 17.5-1.pgdg120+1)
-- Dumped by pg_dump version 17.5

-- Started on 2025-06-16 16:46:50 CEST

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET transaction_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

SET default_tablespace = '';

SET default_table_access_method = heap;

--
-- TOC entry 218 (class 1259 OID 16418)
-- Name: boards; Type: TABLE; Schema: public; Owner: post
--

CREATE TABLE public.boards (
    boa_id bigint NOT NULL,
    boa_name character varying(512) NOT NULL,
    boa_image_link character varying(512),
    man_id bigint NOT NULL,
    cat_id bigint NOT NULL,
    chi_id bigint NOT NULL,
    boa_doc_link character varying(512),
    boa_sch_link character varying(512),
    boa_pin_link character varying(512),
    boa_size_link character varying(512),
    boa_overlay_oid bigint
);


ALTER TABLE public.boards OWNER TO post;

--
-- TOC entry 221 (class 1259 OID 16435)
-- Name: categories; Type: TABLE; Schema: public; Owner: post
--

CREATE TABLE public.categories (
    cat_id bigint NOT NULL,
    cat_name character varying(512) NOT NULL
);


ALTER TABLE public.categories OWNER TO post;

--
-- TOC entry 219 (class 1259 OID 16423)
-- Name: chips; Type: TABLE; Schema: public; Owner: post
--

CREATE TABLE public.chips (
    chi_id bigint NOT NULL,
    chi_name character varying(512) NOT NULL,
    chi_image_link character varying(512),
    chi_doc_link character varying(512)
);


ALTER TABLE public.chips OWNER TO post;

--
-- TOC entry 220 (class 1259 OID 16434)
-- Name: ids; Type: SEQUENCE; Schema: public; Owner: post
--

CREATE SEQUENCE public.ids
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.ids OWNER TO post;

--
-- TOC entry 217 (class 1259 OID 16413)
-- Name: manufacturers; Type: TABLE; Schema: public; Owner: post
--

CREATE TABLE public.manufacturers (
    man_id bigint NOT NULL,
    man_name character varying(512) NOT NULL,
    man_web_link character varying(512)
);


ALTER TABLE public.manufacturers OWNER TO post;

--
-- TOC entry 3225 (class 2606 OID 16433)
-- Name: boards boards_pkey; Type: CONSTRAINT; Schema: public; Owner: post
--

ALTER TABLE ONLY public.boards
    ADD CONSTRAINT boards_pkey PRIMARY KEY (boa_id);


--
-- TOC entry 3229 (class 2606 OID 16441)
-- Name: categories categories_pkey; Type: CONSTRAINT; Schema: public; Owner: post
--

ALTER TABLE ONLY public.categories
    ADD CONSTRAINT categories_pkey PRIMARY KEY (cat_id);


--
-- TOC entry 3227 (class 2606 OID 16429)
-- Name: chips chips_pkey; Type: CONSTRAINT; Schema: public; Owner: post
--

ALTER TABLE ONLY public.chips
    ADD CONSTRAINT chips_pkey PRIMARY KEY (chi_id);


--
-- TOC entry 3223 (class 2606 OID 16431)
-- Name: manufacturers manufacturers_pkey; Type: CONSTRAINT; Schema: public; Owner: post
--

ALTER TABLE ONLY public.manufacturers
    ADD CONSTRAINT manufacturers_pkey PRIMARY KEY (man_id);


-- Completed on 2025-06-16 16:46:50 CEST

--
-- PostgreSQL database dump complete
--

